#include "common/common.h"
#include "thread/ThreadPool.h"
#include "SysInfo.h"
#include "FakeCommand.h"

SysInfo::SysInfo()
:mpThreadPool(NULL)
,mOutStream()
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

	mpThreadPool->addTask(this);

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
			fflush(stdin);
			hint.clear();
		}

		if (mNextCmdLine.length() > 0)
		{
			__replace(mNextCmdLine, "\r", " ");
			__replace(mNextCmdLine, "\n", " ");

			std::vector<std::string> argv;
			__split<>(mNextCmdLine, ' ', argv);
			Command *pCommand = _parseArg(argv);
			if (pCommand)
			{
				mpThreadPool->addTask(pCommand);
			}
			else if (argv.size() == 0)
			{
				hint = ">";
			}
			else
			{
				hint = "Command Invalid!\n>";
			}

			mNextCmdLine.clear();
		}

		mpThreadPool->onMainThreadTick();
		if (mOutStream.size() > 0)
		{
			printf("%s", mOutStream.data());
			mOutStream.clear();
			hint = ">";
		}
	}
}

bool SysInfo::process()
{
	char line[MAX_BUF];
	fgets(line, MAX_BUF, stdin);
	mInputBuffer = line;
	return true;
}

TPTask::TPTaskState SysInfo::presentMainThread()
{
	mNextCmdLine = mInputBuffer;
	mInputBuffer.clear();
	return TPTask_ContinueChildThread;
}

Command* SysInfo::_parseArg(const vector<string> &argv)
{
	Command *pCommand = NULL;
	if (argv.size() > 0)
	{
		int len = argv[0].length();
		if (argv[0] == string("fake"))
		{
			pCommand = new FakeCommand();
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