#ifndef LINUXTIMER_H
#define LINUXTIMER_H

class Timer
{
private:
	unsigned long m_currentTime;
	unsigned long m_lastTime;

	Timer( void ) { Initialize(); }
	~Timer( void ) { }
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
	unsigned long GetTimeMSec( void );
	unsigned long GetTime( void ) { return m_currentTime; }
	unsigned long GetElapsedTime(void) { return m_currentTime - m_lastTime; };
	float GetFps( void ) { return ((float)1000.0 / (float)(m_currentTime - m_lastTime)); }
};

#endif	// LINUXTIMER_H
