#ifndef __COMMANDFACTORYIMPL_H__
#define __COMMANDFACTORYIMPL_H__

#include "CommandFactory.h"

template <class CommandType>
class CommandFactoryImpl : public CommandFactory
{
public:
	virtual std::string getName()
	{
		return CommandType::getName();
	}

	virtual Command* createCommand(Command::Listener *pListener)
	{
		return CommandType::createCommand(pListener);
	}
};

#endif // __COMMANDFACTORYIMPL_H__