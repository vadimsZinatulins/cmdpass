#include "NamedPipe.h"
#include "../config.h"
#include "../utils/Logger.h"
#include "Signal.h"

#include <cstdio>
#include <ios>
#include <sstream>
#include <fstream>

namespace cmdpass
{

namespace ipc
{

std::string NamedPipe::readContent()
{
	Signal<SignalType::User1>::getInstance().wait();

	std::ifstream file(PIPE_FILE_PATH);
	if(file.fail())
	{
		utils::Logger::getInstance().logError("Failed to open PIPE for reading");

		return "";
	}

	std::stringstream buffer;
	buffer <<  file.rdbuf();
	file.close();

	std::string content = std::move(buffer).str();

	std::remove(PIPE_FILE_PATH);

	return std::move(content);
}

void NamedPipe::writeContent(std::string content)
{
	std::ofstream file(PIPE_FILE_PATH, std::ios_base::app);
	if(file.fail())
	{
		utils::Logger::getInstance().logError("Failed to open PIPE for writing");
		return;
	}

	file << content << std::endl;
	file.close();

	Signal<SignalType::User1>::getInstance().send();
}

}

}
