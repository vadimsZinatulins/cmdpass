#include "serviceRequired.h"
#include "getService.h"
#include "createService.h"

namespace cmdpass
{

namespace service
{

void serviceRequired()
{
	if(getService() <= 0)
	{
		createService();
	}
}

}

}
