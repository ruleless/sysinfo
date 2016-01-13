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

	sigar_cpu_info_list_t cpuinfo;
	if (sigar_cpu_info_list_get(s, &cpuinfo) != SIGAR_OK)
	{
		sigar_close(s);
		return 0;
	}

	char line[MAX_BUF] = {0};
	for (int i = 0; i < cpuinfo.number; ++i)
	{
		sigar_cpu_info_t *info = &cpuinfo.data[i];

		sprintf(line, "CPU %d:\n", i+1);
		mMyStream<<line;

#define CPU_FORMAT_STR(field) \
	sprintf(line, "%16s: %s\n", #field, info->field); \
	mMyStream<<line; \

#define CPU_FORMAT_INT(field) \
	sprintf(line, "%16s: %d\n", #field, info->field); \
	mMyStream<<line; \

#define CPU_FORMAT_INT64(field) \
	sprintf(line, "%16s: %llu\n", #field, info->field); \
	mMyStream<<line; \

		CPU_FORMAT_STR(vendor);
		CPU_FORMAT_STR(model);
		CPU_FORMAT_INT(mhz);
		CPU_FORMAT_INT(mhz_max);
		CPU_FORMAT_INT(mhz_min);
		CPU_FORMAT_INT64(cache_size);
		CPU_FORMAT_INT(total_sockets);
		CPU_FORMAT_INT(total_cores);
		CPU_FORMAT_INT(cores_per_socket);
		mMyStream<<"\n";
	}

	sigar_cpu_info_list_destroy(s, &cpuinfo);
	sigar_close(s);
	return 0;
}