#ifndef __MEMINFO_H__
#define __MEMINFO_H__

#include "Command.h"
#include "AutoRegisterCommand.h"

class MemInfo : public Command
{
public:
	COMMAND_DECLARATION(MemInfo);
protected:
	bool mbPrintSwap;
	ulong mInterval;
public:
	MemInfo(Listener *pListener);
	virtual ~MemInfo();

	virtual bool _parseArg(const vector<string> &argv, obuf &outStream);
	virtual ulong _runCommand();
};

#endif // __MEMINFO_H__