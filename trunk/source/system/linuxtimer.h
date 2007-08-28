#ifndef LINUXTIMER_H
#define LINUXTIMER_H

class Timer
{
private:
/*
	unsigned long m_currentTime;
	unsigned long m_lastTime;
*/
	double m_currentTime;
	double m_lastTime;

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

	void Initialize( void ) { m_currentTime = GetTimeSec(); m_lastTime = 0; }
	void Update( void ) { m_lastTime = m_currentTime; m_currentTime = GetTimeSec(); }
//	unsigned long GetTimeSec( void );
	double GetTimeSec( void );
//	unsigned long GetTime( void ) { return m_currentTime; }
	double GetTime( void ) { return m_currentTime; }
	//unsigned long GetElapsedTime(void) { return m_currentTime - m_lastTime; };
	double GetElapsedTime(void) { return m_currentTime - m_lastTime; };
	double GetFps( void ) { return ((double)1.0f / (double)(m_currentTime - m_lastTime)); }
};

#endif	// LINUXTIMER_H
