#include "Service.h"
#include "../ipc/Signal.h"
#include "../config.h"
#include "../ipc/NamedPipe.h"
#include "../utils/Logger.h"

#include <csignal>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/stat.h>

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

void Service::startService()
{
	// Fork of the parent process
	pid_t pid = fork();

	// Exit if failed to create child process
	if(pid < 0) {
		exit(EXIT_FAILURE);
	}

	// Return to the caller
	if(pid > 0) {
		return;
	}

	umask(0);

	utils::Logger::getInstance().open();

	// Create new session ID for the child process
	pid_t sid = setsid();
	if(sid < 0) {
		exit(EXIT_FAILURE);
	}

	// Change current working directory
	if(chdir("/") < 0)
	{
		exit(EXIT_FAILURE);
	}

	// Close standard file descriptors
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	Service(getpid()).run();
}

void Service::stopService()
{
	unsigned int servicePid = getService();
	if(servicePid)
	{
		ipc::NamedPipe::writeContent("stop");
		ipc::Signal<ipc::SignalType::User1, ipc::SignalType::User2>::getInstance().notify(servicePid);
	}
}

unsigned int Service::getService()
{
	std::ifstream pidFile(PID_FILE_PATH);
	if(pidFile.fail())
	{
		return 0;
	}

	int pid;
	pidFile >> pid;
	pidFile.close();

	return pid;
}

void Service::run()
{

	using namespace std::chrono_literals;

	while(true)
	{
		ipc::Signal<ipc::SignalType::User1, ipc::SignalType::User2>::getInstance().wait();
		std::vector<std::string> parameters;
		{
			std::stringstream ss(std::move(ipc::NamedPipe::readContent()));
			std::string param;
			while(ss >> param) parameters.push_back(std::move(param));
		}

		utils::Logger::getInstance().logInfo("New action from pid: " + parameters[0]);
		if(parameters[1] == "stop") termiate(0);
	}
}

}

}
