#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "common/common.h"
#include "common/Buffer.h"
#include "thread/ThreadTask.h"

using namespace std;

class Command : public TPTask
{
protected:
	obuf mMyStream;
	string mCommandName;
	ulong mExRunTime;
	ulong mNextInterval;
public:
	Command();
	virtual ~Command();

	bool parseCommond(const vector<string> &argv);
	virtual bool _parseArg(const vector<string> &argv) { return true; }

	virtual bool process();
	virtual ulong _runCommand() = 0;

	virtual TPTask::TPTaskState presentMainThread();
};

#endif // __COMMAND_H__