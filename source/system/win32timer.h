
#ifndef WIN32TIMER_H
#define WIN32TIMER_H

#include <windows.h>
#include <mmsystem.h>

#include "itimer.h"

#pragma comment(lib,"winmm.lib")

class Timer : public ITimer
{
private:
	float PreviousTime, CurrentTime, ElapsedTime;
	float FPSElapsedTime;
	int FPSCounter, FPS;

	__int64       frequency;									// Timer Frequency
	float         resolution;									// Timer Resolution
	unsigned long mm_timer_start;								// Multimedia Timer Start Value
	unsigned long mm_timer_elapsed;								// Multimedia Timer Elapsed Time
	bool		  performance_timer;							// Using The Performance Timer?
	__int64       performance_timer_start;						// Performance Timer Start Value
	__int64       performance_timer_elapsed;					// Performance Timer Elapsed Time

public:
	static Timer &Instance()
	{
		static Timer oTimer;
		return oTimer;
	}

	Timer();
	void Initialize();
	void Update();
	float GetTime() const;
	float GetElapsedTime() const;
	int GetFps(void) const { return FPS; }
};

#endif	// WIN32TIMER_H
