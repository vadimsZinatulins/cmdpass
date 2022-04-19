#pragma once

#include <string>

namespace cmdpass
{

namespace ipc
{

struct NamedPipe
{
	static std::string readContent();
	static void writeContent(std::string conent);
};

}

}
