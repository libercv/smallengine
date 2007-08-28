#include "linuxtimer.h"
#include "sys/time.h"
#include <iostream>

//unsigned long Timer::GetTimeSec( void )
double Timer::GetTimeSec( void )  
{ 
	//unsigned long ticks;
	double ticks;
	struct timeval now;

	gettimeofday(&now, NULL);
	
	// tv_sec nos la el tiempo con precisión de segundos
	//ticks=now.tv_sec * 1000l;
	ticks=now.tv_sec;
	
	// millonésimas de segundo desde el último segundo marcado por tv_sec. tv_usec/1000 = 1 milisegundo
	ticks+= (float)now.tv_usec / 1000000.0f;

	// Devolvemos el tiempo con precisión de segundos
	return ticks;
}
