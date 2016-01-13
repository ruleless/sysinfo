#ifndef __MEMINFO_H__
#define __MEMINFO_H__

#include "Command.h"
#include "AutoRegisterCommand.h"

class MemInfo : public Command
{
public:
	COMMAND_DECLARATION(MemInfo);
protected:
public:
	MemInfo(Listener *pListener);
	virtual ~MemInfo();

	virtual ulong _runCommand();
};

#endif // __MEMINFO_H__