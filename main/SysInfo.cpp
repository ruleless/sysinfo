#include "common/common.h"
#include "thread/ThreadPool.h"
#include "SysInfo.h"
#include "CommandFactoryRegistry.h"

SysInfo::SysInfo()
:mpThreadPool(NULL)
,mbQuit(false)
,mOutStream()
,mpInput(NULL)
,mCommandList()
{
}

SysInfo::~SysInfo()
{
}

bool SysInfo::initialise()
{
	mpThreadPool = new ThreadPool();
	if (!mpThreadPool->createThreadPool(10, 20, 30))
	{
		return false;
	}

	mpInput = new Input(this);
	mpThreadPool->addTask(mpInput);

	return true;
}

void SysInfo::finalisze()
{
	mpThreadPool->finalise();
	delete mpThreadPool;
	mpThreadPool = NULL;
}

void SysInfo::run()
{
	std::string hint = ">";
	while (true)
	{
		if (hint.length() > 0)
		{
			printf("%s", hint.c_str());
			fflush(stdout);
			hint.clear();
		}

		if (mpInput)
		{
			std::string cmdLine = mpInput->getCmdLine();
			if (cmdLine.length() > 0)
			{
				__replace(cmdLine, "\r", " ");
				__replace(cmdLine, "\n", " ");

				std::vector<std::string> argv;
				__split<>(cmdLine, ' ', argv);
				Command *pCommand = _parseUserCommand(argv);
				if (pCommand)
				{
					mCommandList.insert(pCommand);
					mpThreadPool->addTask(pCommand);
				}
				else if (argv.size() > 0)
				{
					if (!_parseSysCommand(argv))
					{
						hint = "Command Invalid!\n>";
					}
				}
				else
				{
					hint = ">";
				}

				mpInput->clearCmdLine();
			}
		}

		mpThreadPool->onMainThreadTick();
		if (mOutStream.size() > 0)
		{
			printf("%s", mOutStream.data());
			mOutStream.clear();
			hint = ">";
		}

		if (mbQuit)
		{
			if (mpThreadPool->currentFreeThreadCount() == mpThreadPool->currentThreadCount() && mpThreadPool->finiTaskSize() == 0)
			{
				break;
			}
		}
	}
}

Command* SysInfo::_parseUserCommand(const vector<string> &argv)
{
	Command *pCommand = NULL;
	if (argv.size() > 0)
	{
		CommandFactory *pFactory = CommandFactoryRegistry::getRegistry()->getCommandFactory(argv[0]);
		if (pFactory)
		{
			pCommand = pFactory->createCommand(this);
		}		
	}

	if (pCommand)
	{
		if (!pCommand->parseCommond(argv))
		{
			delete pCommand;
			pCommand = NULL;
		}
	}
	return pCommand;
}

bool SysInfo::_parseSysCommand(const vector<string> &argv)
{
	bool isSysCmd = true;
	bool stopAllCmd = false;
	if (argv[0] == "q")
	{
		stopAllCmd = true;
	}
	else if (argv[0] == "quit")
	{
		stopAllCmd = true;
		mbQuit = true;
	}
	else
	{
		isSysCmd = false;
	}

	CommandList::iterator it = mCommandList.begin();
	for (; it != mCommandList.end(); ++it)
	{
		(*it)->forceQuit(true);
	}

	return isSysCmd;
}

void SysInfo::onCommandDestroy(Command *pCmd)
{
	CommandList::iterator it = mCommandList.find(pCmd);
	mCommandList.erase(it);
}

bool SysInfo::onOutputStream(Command *pCmd, const obuf& ob)
{
	mOutStream<<ob.data();
	return true;
}

void SysInfo::onInputDestroy(Input *pInput)
{
	mpInput = NULL;
}


SysInfo *gpSysInfo = NULL;

int main(int argc, char *argv[])
{
	gpSysInfo = new SysInfo();
	if (!gpSysInfo->initialise())
	{
		delete gpSysInfo;
		return false;
	}

	gpSysInfo->run();
	
	gpSysInfo->finalisze();
	delete gpSysInfo;
	return 0;
}