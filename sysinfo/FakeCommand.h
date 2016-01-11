#ifndef __FAKECOMMAND_H__
#define __FAKECOMMAND_H__

#include "Command.h"
#include "AutoRegisterCommand.h"

class FakeCommand : public Command
{
public:
	COMMAND_DECLARATION(FakeCommand);
public:
	FakeCommand(Listener *pListener)
		:Command(pListener)
	{
	}

	virtual ~FakeCommand() {}

	virtual ulong _runCommand();
};

#endif // __FAKECOMMAND_H__