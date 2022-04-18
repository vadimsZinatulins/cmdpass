#pragma once

#include <string>

namespace cmdpass
{

namespace ipc
{

struct NamedPipe
{
	static std::string getContent();
};

}

}
