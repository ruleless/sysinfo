#ifndef __CPUINFO_H__
#define __CPUINFO_H__

#include "Command.h"
#include "AutoRegisterCommand.h"

class CpuInfo : public Command
{
public:
	COMMAND_DECLARATION(CpuInfo);
protected:	
public:
	CpuInfo(Listener *pListener);
	virtual ~CpuInfo();

	virtual ulong _runCommand();
};

#endif // __CPUINFO_H__