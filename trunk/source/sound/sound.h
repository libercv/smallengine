
#ifndef SOUND_H
#define SOUND_H

#include "fmod/fmod.h"

#include "../singleton.h"
#include "../log.h"

namespace Small
{

// PENDIENTE: implementar interfaz ISubSystem que obligue a implementar el método Update().
// Hacer que Timer, Input, Sound, etc... implementen ISubSystem.
class SoundManager : public Singleton<SoundManager>
{
	friend class Singleton<SoundManager>;

private:
	FSOUND_SAMPLE *Ambiente, *Paso, *Boing, *PlayerDead, *Bola;

protected:
	SoundManager(void);

public:
	void PlayPaso(void);
	void PlayBola(void);
	void PlayBoing(void);
	void PlayPlayerDead(void);
	void Update(void) {};

};


}

#endif
