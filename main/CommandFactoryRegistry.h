#ifndef __COMMANDFACTORYREGISTRY_H__
#define __COMMANDFACTORYREGISTRY_H__

#include "CommandFactory.h"

class CommandFactoryRegistry
{
protected:
	typedef std::vector<CommandFactory *> FactoryList;
	FactoryList mFactories;
	static bool mbValid;
public:
	CommandFactoryRegistry();
	~CommandFactoryRegistry();

	static CommandFactoryRegistry* getRegistry();
	static bool isValid();

	void registerFactory(CommandFactory *factory);
	void unregisterFactory(CommandFactory *factory);

	CommandFactory* getCommandFactory(const std::string cmdName);
};

#endif // __COMMANDFACTORYREGISTRY_H__