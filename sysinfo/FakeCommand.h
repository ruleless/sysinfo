#ifndef __FAKECOMMAND_H__
#define __FAKECOMMAND_H__

#include "Command.h"

class FakeCommand : public Command
{
protected:
public:
	FakeCommand()
	{
	}

	virtual ~FakeCommand() {}

	virtual ulong _runCommand()
	{
		mMyStream<<"I am Fake Command!\n";
		return 0;
	}
};

#endif // __FAKECOMMAND_H__