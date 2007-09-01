
#ifndef ITIMER_H
#define ITIMER_H

class ITimer
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual float GetTime() const = 0;
	virtual float GetElapsedTime() const = 0;
	virtual int GetFps(void) const = 0;
	/*
	Pause
	Resume
	*/
};

#endif	// ITIMER_H
