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

	void run();
private:
};

}

}
