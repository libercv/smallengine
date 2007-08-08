
#ifndef WIN32TIMER_H
#define WIN32TIMER_H

#include <time.h>
#include <windows.h>

#include "itimer.h"

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

#endif	// WIN32TIMER_H
