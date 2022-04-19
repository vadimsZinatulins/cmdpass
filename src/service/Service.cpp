#include "Service.h"
#include "../ipc/Signal.h"
#include "../config.h"
#include "../ipc/NamedPipe.h"
#include "../utils/Logger.h"
#include "../utils/ArgParser.h"

#include <csignal>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

namespace cmdpass
{

namespace service
{

void termiate(int signal)
{
	utils::Logger::getInstance().logInfo("cmdpassd service is terminating!");

	// Close the logger file
	utils::Logger::getInstance().close();

	std::remove(PID_FILE_PATH);
	
	exit(EXIT_FAILURE);
}

Service::Service(int pid)
{
	std::signal(SIGABRT, termiate);
	std::signal(SIGFPE, termiate);
	std::signal(SIGILL, termiate);
	std::signal(SIGINT, termiate);
	std::signal(SIGSEGV, termiate);
	std::signal(SIGTERM, termiate);
	std::signal(SIGKILL, termiate);

	std::ofstream pidFile(PID_FILE_PATH);
	if(pidFile.fail())
	{
		utils::Logger::getInstance().logError("Failed to create PID file");
		exit(EXIT_FAILURE);
	}

	pidFile << pid << std::endl;
	pidFile.close();

	utils::Logger::getInstance().logInfo("cmdpassd service initialized with PID: " + std::to_string(pid));
}

Service::~Service()
{

}

void Service::run()
{

	using namespace std::chrono_literals;

	while(true)
	{
		std::string content = ipc::NamedPipe::readContent();
		utils::Logger::getInstance().logInfo("Action received: " + content);

		utils::ArgParser parser(std::move(content));
		parser.add({ "stop" }, []{ termiate(0); });

		parser.parse();
	}
}

}

}
