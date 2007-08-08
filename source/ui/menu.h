#ifndef MENU_H
#define MENU_H

#ifdef WINDOWS
#include <windows.h>
#endif

#include <math.h>

#include <vector>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef WINDOWS
	#include "../system/win32input.h"
#else
	#include "../system/linuxinput.h"
#endif

// PENDIENTE: quiz� "menu" no deber�a de ver "texture"... no s�
#include "../graphics/texture.h"

#include "../engine.h"


/*
#include "game.h"
*/

namespace Small
{

class Menu
{
private:
	std::vector<std::string> Items;

	Menu(void);
	~Menu(void) {};
	Menu(Menu const&) {};
	Menu &operator=(Menu const&) {};

	short SelectedItemIndex;

public:
	static Menu &Instance()
	{
		static Menu oMenu;
		return oMenu;
	}

	// PENDIENTE: temporal. Solo para pruebas
	int texture;

	void Load(void) {};

	void Update(void);
	void Render(void);
};

} // namespace Small

#endif
