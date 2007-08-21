#ifndef STATEMENU_H
#define STATEMENU_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <math.h>

#include <vector>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>

/*
#ifdef _WIN32
	#include "system/win32input.h"
#else
	#include "system/linuxinput.h"
#endif
*/

#include "system/input.h"

// PENDIENTE: quiza "menu" no deberia de ver "texture"...
#include "graphics/texture.h"

#include "istate.h"
#include "singleton.h"

// PENDIENTE: stateMenu no deber�a ver a stateGame. Probablemente solo necesitemos una captura de un frame que nos la
// puede servir engine. Pensar.
#include "stategame.h"

namespace Small
{
class StateMenu : public Singleton<StateMenu>, public IState
{
	friend class Singleton<StateMenu>;

private:
	std::vector<std::string> Items;
	short SelectedItemIndex;

protected:
	StateMenu(void);
	~StateMenu(void) {};

public:
	// PENDIENTE: temporal. Solo para pruebas
	int texture, mask; 

	void Load(void) {};

	EngineStateEnum Update(float ElapsedTime);
	void Render(void);
};
} // namespace Small

#endif
