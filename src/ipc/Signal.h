#pragma once

#include "../service/getService.h"
#include "../utils/Logger.h"

#include <mutex>
#include <condition_variable>
#include <csignal>

namespace cmdpass
{

namespace ipc
{

enum class SignalType { User1 = SIGUSR1, User2 = SIGUSR2 };

template<SignalType type>
class Signal
{
public:
	static Signal &getInstance()
	{
		static Signal instance;

		return instance;
	}

	void wait()
	{
		auto lock = std::unique_lock(m_mutex);
		m_cv.wait(lock, [this]{ return m_isSet; });

		m_isSet = false;
	}

	void send()
	{
		unsigned int pid = service::getService();
		if(!pid)
		{
			utils::Logger::getInstance().logError("No cmdpassd service found.");
			return;
		}

		kill(pid, static_cast<int>(type));
	}
private:
	Signal() : m_isSet(false)
	{
		std::signal(static_cast<int>(type), [](int signal){	Signal<type>::getInstance().set(); });
	}

	~Signal()
	{
	
	}

	void set()
	{
		auto lock = std::unique_lock(m_mutex);
		m_isSet = true;

		m_cv.notify_one();
	}

	std::mutex m_mutex;
	std::condition_variable m_cv;

	bool m_isSet;
};

}

}
