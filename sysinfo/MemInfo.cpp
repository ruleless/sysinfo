#include "MemInfo.h"
#include "sigar.h"

COMMAND_IMPLEMENTION(MemInfo, "mem");
COMMAND_FACTORY_REGISTRATION(MemInfo);

MemInfo::MemInfo(Listener *pListener)
:Command(pListener)
{	
}

MemInfo::~MemInfo()
{
}

ulong MemInfo::_runCommand()
{
	return 0;
}