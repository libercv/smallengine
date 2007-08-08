
#ifndef ITIMER_H
#define ITIMER_H

class ITimer
{
public:
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual unsigned long GetTimeMSec(void) = 0;
	virtual unsigned long GetTime(void) = 0;
	virtual unsigned long GetElapsedTime(void) = 0;
	virtual float GetFps(void) = 0;
};

#endif	// ITIMER_H
