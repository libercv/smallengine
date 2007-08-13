#ifndef TIMER_H
#define TIMER_H

#ifdef _WIN32
	#include "win32timer.h"
#else
	#include "linuxtimer.h"
#endif

#endif // TIMER_H
