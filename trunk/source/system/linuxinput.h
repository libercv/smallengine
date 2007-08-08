/*
	Clase input para linux. Implementa la interfaz IInput
*/

#ifndef LINUXINPUT_H
#define LINUXINPUT_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "iinput.h"



// Clase Input que implementa los metodos dependientes del
// sistema operativo de InputBase
class Input:public IInput
{
private:
	bool KeysState[MAX_KEYS];
	bool KeysPressed[MAX_KEYS];
	bool KeysReleased[MAX_KEYS];

	// FIXME: Numero maximo de teclas
	Keys KeysTranslated[65535];

	//void ManageKeyPressed(KeySym key, bool pressed);
	void _KeyPressed(Keys key, bool pressed);

	int x, y, dx, dy;
public:
	static Input &Instance()
	{
		static Input oInput;
		return oInput;
	}	
	Input(Input const&) {};
	Input &operator=(Input const&) {};
	Input();

	void OnEvent( void *Event );
	bool IsKeyPressed(Keys Key);
	bool IsKeyReleased(Keys Key);
	bool GetKeyState(Keys Key);
	bool IsMouseButtonPressed(MouseButtons Button);
	void GetMousePosition(int *outX, int *outY);
	void Update(void);
	void GetMouseMotion(int *, int *);

	void ResetBuffers(void);
	
};
#endif // LINUXINPUT_H
