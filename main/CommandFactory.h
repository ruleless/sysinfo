#ifndef __COMMANDFACTORY_H__
#define __COMMANDFACTORY_H__

#include "Command.h"

class CommandFactory
{
public:
	virtual std::string getName() = 0;
	virtual Command* createCommand(Command::Listener *pListener) = 0;
};

#endif // __COMMANDFACTORY_H__