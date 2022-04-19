#include "Logger.h"
#include "../config.h"

#include <ctime>
#include <ios>
#include <ostream>
#include <string>

namespace cmdpass
{

namespace utils
{

Logger &Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::open()
{
	m_output.open(LOG_FILE_PATH, std::ios_base::app);
}

void Logger::close()
{
	m_output.close();
}

void Logger::logInfo(std::string message)
{
	log("#### INFO ####", std::move(message));
}

void Logger::logWarning(std::string message)
{
	log("#### WARNING ####", std::move(message));
}

void Logger::logError(std::string message)
{
	log("#### ERROR ####", std::move(message));
}

void Logger::setSource(std::string newSource)
{
	m_source = newSource;
}

void Logger::log(std::string type, std::string message)
{
	open();

	if(m_output.is_open())
	{
		char timeBuffer[25];
		std::string time;
		std::time_t now = std::time(nullptr);
		if(std::strftime(timeBuffer, sizeof(timeBuffer), "[%d/%m/%Y %H:%M:%S]", std::localtime(&now)))
		{
			time = "At " + std::string(timeBuffer) + '\n';
		}

		m_output << type << '\n' << "By [" << m_source << "] " << time << message << '\n' << std::endl;
	}

	close();
}

}

}
