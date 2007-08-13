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

#ifdef _WIN32
	#include "system/win32input.h"
#else
	#include "system/linuxinput.h"
#endif

// PENDIENTE: quizá "menu" no debería de ver "texture"... no sé
#include "graphics/texture.h"

#include "state.h"

// PENDIENTE: stateMenu no debería ver a stateGame. Probablemente solo necesitemos una captura de un frame que nos la
// puede servir engine. Pensar.
#include "stateGame.h"

namespace Small
{

	class StateMenu : State
{
private:
	std::vector<std::string> Items;

	StateMenu(void);
	~StateMenu(void) {};
	StateMenu(StateMenu const&) {};
	StateMenu &operator=(StateMenu const&) {};

	short SelectedItemIndex;

public:
	static StateMenu &Instance()
	{
		static StateMenu oStateMenu;
		return oStateMenu;
	}

	// PENDIENTE: temporal. Solo para pruebas
	int texture;

	void Load(void) {};

	StateId Update(float ElapsedTime);
	void Render(void);
};

} // namespace Small

#endif
