#include "CpuInfo.h"
#include "sigar.h"

COMMAND_IMPLEMENTION(CpuInfo, "cpu");
COMMAND_FACTORY_REGISTRATION(CpuInfo);

CpuInfo::CpuInfo(Listener *pListener)
:Command(pListener)
{	
}

CpuInfo::~CpuInfo()
{
}

ulong CpuInfo::_runCommand()
{
	sigar_t *s = NULL;
	if (sigar_open(&s) != SIGAR_OK)
	{
		return 0;
	}

	sigar_cpu_t cpuinfo;
	if (sigar_cpu_get(s, &cpuinfo) != SIGAR_OK)
	{
		sigar_close(s);
		return 0;
	}

	return 0;
}