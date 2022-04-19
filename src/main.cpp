#include "utils/ArgParser.h"
#include "service/startService.h"
#include "service/stopService.h"

#include <iostream>

int main(int argc, char *argv[])
{
	cmdpass::utils::ArgParser parser(argc, argv);

	parser.add({ "--start-service" }, []{ cmdpass::service::startService(); });
	parser.add({ "--stop-service" }, []{ cmdpass::service::stopService(); });
	// TODO:
	// Implement help argument
	parser.add({ "--help", "-h" }, []{});
	// TODO:
	// Implement version argument
	parser.add({ "--version", "-v" }, []{});

	parser.parse();

	return 0;
}
