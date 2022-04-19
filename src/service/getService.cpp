#include "getService.h"
#include "../config.h"

#include <fstream>

namespace cmdpass
{

namespace service
{
	
unsigned int getService()
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

}

}
