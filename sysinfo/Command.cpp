#include "Command.h"
#include "SysInfo.h"
#include "common/timestamp.h"

Command::Command()
:mMyStream()
,mCommandName("")
,mExRunTime(0)
,mNextInterval(0)
{
}

Command::~Command()
{
}

bool Command::parseCommond(const vector<string> &argv)
{
	if (argv.size() >= 1)
	{
		mCommandName = argv[0];
		return _parseArg(argv);
	}
	return false;
}

bool Command::process()
{
	mNextInterval = _runCommand();
	mExRunTime = getTickCount();

	return true;
}

TPTask::TPTaskState Command::presentMainThread()
{
	TPTask::TPTaskState retState = TPTask_Completed;
	if (0 == mNextInterval)
	{
		retState = TPTask_Completed;
	}
	else if (getTickCount() < mExRunTime+mNextInterval)
	{
		retState = TPTask_ContinueMainThread;
	}
	else
	{
		retState = TPTask_ContinueChildThread;
	}
	gpSysInfo->getOutStream()<<mMyStream.data();

	return retState;
}