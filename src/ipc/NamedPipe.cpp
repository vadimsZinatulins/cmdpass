#include "NamedPipe.h"
#include "../config.h"
#include "Signal.h"

#include <cstdio>
#include <sstream>
#include <fstream>

namespace cmdpass
{

namespace ipc
{

std::string NamedPipe::getContent()
{
	Signal<SignalType::User1>::getInstance().wait();

	std::ifstream file(PIPE_FILE_PATH);
	if(file.fail())
	{
		// TODO:
		// Log the error

		return "";
	}

	std::stringstream buffer;
	buffer <<  file.rdbuf();
	file.close();

	std::string content = std::move(buffer).str();

	std::remove(PIPE_FILE_PATH);

	return std::move(content);
}

}

}
