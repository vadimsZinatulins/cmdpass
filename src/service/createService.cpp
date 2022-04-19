#include "createService.h"
#include "Service.h"
#include "../utils/Logger.h"

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

namespace cmdpass
{

namespace service
{

void createService()
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

	Service(pid).run();
}

}

}
