#pragma once

namespace cmdpass
{

namespace service
{

class Service
{
public:
	Service(int pid);
	~Service();

	static void startService();
	static void stopService();
	static unsigned int getService();

	void run();
private:
};

}

}
