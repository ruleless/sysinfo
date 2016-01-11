#ifndef __AUTOREGISTERCOMMAND_H__
#define __AUTOREGISTERCOMMAND_H__

#include "CommandFactoryImpl.h"
#include "CommandFactoryRegistry.h"

template<class CommandType>
class AutoRegisterCommand
{
public:
	AutoRegisterCommand()
		: mRegistry(CommandFactoryRegistry::getRegistry())
	{
		mRegistry->registerFactory(&mFactory);
	}

	~AutoRegisterCommand()
	{
		if (CommandFactoryRegistry::isValid())
		{
			mRegistry->unregisterFactory(&mFactory);
		}
	}
private:
	CommandFactoryRegistry *mRegistry;
	CommandFactoryImpl<CommandType> mFactory;
};


#define COMMAND_DECLARATION(CommandType) \
	static std::string getName(); \
	static Command* createCommand(Command::Listener *)


#define COMMAND_IMPLEMENTION(CommandType, cmdName) \
	std::string CommandType::getName() \
	{ \
		return cmdName; \
	} \
	Command* CommandType::createCommand(Command::Listener *pListener) \
	{ \
		return new CommandType(pListener); \
	} \
	

#define COMMAND_FACTORY_REGISTRATION(CommandType) \
	static AutoRegisterCommand<CommandType> _autoRegisterRegistry_##CommandType

#endif // __AUTOREGISTERCOMMAND_H__