#ifndef __INPUT_H__
#define __INPUT_H__

#include "thread/ThreadTask.h"

class Input : public TPTask
{
public:
	struct Listener 
	{
		virtual void onInputDestroy(Input *pInput) = 0;
	};
protected:
	std::string mInputBuffer;
	std::string mNextCmdLine;
	Listener *mpListener;
public:
	Input(Listener *pListener);
	virtual ~Input();

	inline const std::string& getCmdLine()
	{
		return mNextCmdLine;
	}
	inline void clearCmdLine()
	{
		mNextCmdLine.clear();
	}

	virtual bool process();
	virtual TPTask::TPTaskState presentMainThread();
};

#endif // __INPUT_H__