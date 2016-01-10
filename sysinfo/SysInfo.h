#ifndef __SYSINFO_H__
#define __SYSINFO_H__

#include "common/common.h"
#include "common/Buffer.h"

using namespace std;

class Command;
class ThreadPool;
class SysInfo : public TPTask
{
protected:
	ThreadPool *mpThreadPool;
	std::string mInputBuffer;
	std::string mNextCmdLine;
	obuf mOutStream;
public:
	SysInfo();
	~SysInfo();

	bool initialise();
	void finalisze();

	void run();
	virtual bool process();
	virtual TPTask::TPTaskState presentMainThread();
	Command* _parseArg(const vector<string> &argv);

	inline obuf& getOutStream()
	{
		return mOutStream;
	}
};

extern SysInfo *gpSysInfo;

#endif // __SYSINFO_H__