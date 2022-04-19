#include "stopService.h"
#include "../ipc/NamedPipe.h"

namespace cmdpass
{

namespace service
{

void stopService()
{
	ipc::NamedPipe::writeContent("stop");
}

}

}
