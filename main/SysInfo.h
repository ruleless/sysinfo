#ifndef __SYSINFO_H__
#define __SYSINFO_H__

#include "common.h"
#include "Buffer.h"
#include "Command.h"
#include "Input.h"

using namespace std;

class ThreadPool;
class SysInfo : public Command::Listener, public Input::Listener
{
protected:
	ThreadPool *mpThreadPool;
	bool mbQuit;
	obuf mOutStream;

	Input *mpInput;
	
	typedef std::set<Command *> CommandList;
	CommandList mCommandList;
public:
	SysInfo();
	~SysInfo();

	bool initialise();
	void finalisze();

	void run();
	Command* _parseUserCommand(const vector<string> &argv);
	bool _parseSysCommand(const vector<string> &argv);

	virtual void onCommandDestroy(Command *pCmd);
	virtual bool onOutputStream(Command *pCmd, const obuf& ob);
	virtual void onInputDestroy(Input *pInput);

	inline bool quit()
	{
		return mbQuit;
	}
	inline void quit(bool b)
	{
		mbQuit = b;
	}
};

extern SysInfo *gpSysInfo;

#endif // __SYSINFO_H__