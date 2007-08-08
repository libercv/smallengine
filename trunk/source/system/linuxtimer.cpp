#include "linuxtimer.h"
#include "sys/time.h"
#include <iostream>

unsigned long Timer::GetTimeMSec( void ) 
{ 
	unsigned long ticks;
	struct timeval now;

	gettimeofday(&now, NULL);
	
	// tv_sec nos la el tiempo con precisión de segundos
	ticks=now.tv_sec * 1000l;

	// millonésimas de segundo desde el último segundo marcado por tv_sec. tv_usec/1000 = 1 milisegundo
	ticks+=now.tv_usec / 1000l;

	// Devolvemos el tiempo con precisión de milisegundos
	return ticks;
}
