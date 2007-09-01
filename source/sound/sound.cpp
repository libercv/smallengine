
#include "sound.h"

namespace Small
{
SoundManager::SoundManager()
{
	const char FileAmbiente[] = "resources/sound/wavs/al_an_bugscave2.wav\0";
	const char FilePaso[] = "resources/sound/wavs/paso.wav\0";
	const char FileBoing[] = "resources/sound/wavs/boing.ogg\0";
	const char FilePD[] = "resources/sound/wavs/playerdead.ogg\0";

	if( !FSOUND_Init(44000, 8, 0) )
    {
		Log::Instance().Write("Error inicializando sonido: %d\n", FSOUND_GetError());
    }

    Ambiente = FSOUND_Sample_Load(FSOUND_UNMANAGED, FileAmbiente, FSOUND_LOOP_NORMAL | FSOUND_NORMAL | FSOUND_HW2D, 0, 0);
    if( !Ambiente )
		Log::Instance().Write("Error %d cargando fichero de sonido %s", FSOUND_GetError(), FileAmbiente);

    Paso = FSOUND_Sample_Load(FSOUND_UNMANAGED, FilePaso, FSOUND_LOOP_OFF | FSOUND_NORMAL | FSOUND_HW2D, 0, 0);
    if( !Paso )
		Log::Instance().Write("Error %d cargando fichero de sonido %s", FSOUND_GetError(), FilePaso);

    Boing = FSOUND_Sample_Load(FSOUND_UNMANAGED, FileBoing, FSOUND_LOOP_OFF | FSOUND_NORMAL | FSOUND_HW2D, 0, 0);
    if( !Boing )
		Log::Instance().Write("Error %d cargando fichero de sonido %s", FSOUND_GetError(), FileBoing);

    PlayerDead = FSOUND_Sample_Load(FSOUND_UNMANAGED, FilePD, FSOUND_LOOP_OFF | FSOUND_NORMAL | FSOUND_HW2D, 0, 0);
    if( !PlayerDead )
		Log::Instance().Write("Error %d cargando fichero de sonido %s", FSOUND_GetError(), FilePD);

	FSOUND_PlaySound(FSOUND_FREE, Ambiente);
}

void SoundManager::PlayPaso(void)
{
	FSOUND_PlaySound(FSOUND_FREE, Paso);
}

void SoundManager::PlayBoing(void)
{
	FSOUND_PlaySound(FSOUND_FREE, Boing);
}

void SoundManager::PlayPlayerDead(void)
{
	FSOUND_PlaySound(FSOUND_FREE, PlayerDead);
}

} // namespace Small



