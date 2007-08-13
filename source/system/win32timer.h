
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
};

/*
class Timer : public ITimer
{
private:
	unsigned long m_currentTime;
	unsigned long m_lastTime;

	Timer( void ) { Initialize(); }
	~Timer( void ) {}
	Timer(Timer const&) {}
	Timer &operator=(Timer const&) {}

public:
	static Timer &Instance()
	{
		static Timer oTimer;
		return oTimer;
	}

	void Initialize( void ) { m_currentTime = GetTimeMSec(); m_lastTime = 0; }
	void Update( void ) { m_lastTime = m_currentTime; m_currentTime = GetTimeMSec(); }
	unsigned long GetTimeMSec( void ) { return GetTickCount(); }
	unsigned long GetTime( void ) { return m_currentTime; }
	unsigned long GetElapsedTime( void ) { return m_currentTime-m_lastTime; }
	float GetFps( void ) { return ((float)1000.0 / (float)(m_currentTime - m_lastTime)); }
};
*/

#endif	// WIN32TIMER_H
