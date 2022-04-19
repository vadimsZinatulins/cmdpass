#pragma once

#include <string>
#include <fstream>

namespace cmdpass
{

namespace utils
{

class Logger
{
public:
	static Logger &getInstance();

	void open();
	void close();

	void logInfo(std::string message);
	void logWarning(std::string message);
	void logError(std::string message);
private:
	Logger() = default;
	~Logger() = default;

	void log(std::string type, std::string message);
	std::ofstream m_output;
};

}

}
