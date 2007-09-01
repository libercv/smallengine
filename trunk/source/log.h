#ifndef LOG_H
#define LOG_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include <time.h>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "singleton.h"

namespace Small
{
class Log : public Singleton<Log>
{
	friend class Singleton<Log>;

private:
	std::ofstream LogFile;
	
protected:
	Log();
	~Log();

public:
	void Write(const char *fmt, ...);
	void LuaWrite(const char *Text);

}; // class Log : public Singleton
} // namespace Small

#endif // LOG_H
