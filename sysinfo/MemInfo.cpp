#include "MemInfo.h"
#include "utils.h"

COMMAND_IMPLEMENTION(MemInfo, "mem");
COMMAND_FACTORY_REGISTRATION(MemInfo);

MemInfo::MemInfo(Listener *pListener)
:Command(pListener)
,mbPrintSwap(false)
,mInterval(0)
{	
}

MemInfo::~MemInfo()
{
}

bool MemInfo::_parseArg(const vector<string> &argv, obuf &outStream)
{
	int n = argv.size();
	for (int i = 1; i < n; )
	{
		const char *argItem = argv[i].c_str();
		int argItemLen = strlen(argItem);
		bool bLoopPrint = false;
		if (argItemLen > 0 && argItem[0] == '-')
		{
			for (int j = 1; j < argItemLen; ++j)
			{
				switch (argItem[j])
				{
				case 's':
					mbPrintSwap = true;
					break;
				case 't':
					bLoopPrint = true;
					break;
				default:
					break;
				}
			}
		}

		if (bLoopPrint)
		{
			if (i+1 < n)
			{
				mInterval = atoi(argv[i+1].c_str());
				if (mInterval <= 0)
				{
					outStream<<"Please Assign Interval!\n";
					return false;
				}
				i += 2;
				continue;
			}
		}

		++i;
	}
	return true;
}

ulong MemInfo::_runCommand()
{
	sigar_t *s = NULL;
	if (sigar_open(&s) != SIGAR_OK)
	{
		return 0;
	}

	char line[MAX_BUF] = {0};

#define MEM_FORMAT_DOUBLE(field) \
	sprintf(line, "%12s: %.1lf %%\n", #field, memInfo.field); \
	mMyStream<<line; \

#define MEM_FORMAT_INT64(field) \
	sprintf(line, "%12s: %s B\n", #field, formatInteger(memInfo.field)); \
	mMyStream<<line; \

	if (mbPrintSwap)
	{
		sigar_swap_t memInfo;
		if (sigar_swap_get(s, &memInfo) != SIGAR_OK)
		{
			sigar_close(s);
			return 0;
		}

		MEM_FORMAT_INT64(total);
		MEM_FORMAT_INT64(used);
		MEM_FORMAT_INT64(free);
		MEM_FORMAT_INT64(page_in);
		MEM_FORMAT_INT64(page_out);
	}
	else
	{
		sigar_mem_t memInfo;
		if (sigar_mem_get(s, &memInfo) != SIGAR_OK)
		{
			sigar_close(s);
			return 0;
		}

		MEM_FORMAT_INT64(ram);
		MEM_FORMAT_INT64(total);
		MEM_FORMAT_INT64(used);
		MEM_FORMAT_INT64(free);
		MEM_FORMAT_INT64(actual_used);
		MEM_FORMAT_INT64(actual_free);
		MEM_FORMAT_DOUBLE(used_percent);
		MEM_FORMAT_DOUBLE(free_percent);
	}

	sigar_close(s);	
	return mInterval;
}