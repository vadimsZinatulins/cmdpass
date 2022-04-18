#include "service/createService.h"

#include <iostream>

int main(int argc, char *argv[])
{
	cmdpass::service::createService();

	std::cout << "Service created!" << std::endl;

	return 0;
}
