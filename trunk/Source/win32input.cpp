
#include "win32input.h"

namespace Small
{
	Input::Input(void)
	{
		ResetBuffers();

		// PENDIENTE: sacar la configuraci�n de teclas de un archivo.
		memset(KeyMap,MAX_KEYS,256);

		KeyMap['S'] = KeyDown;		KeyMap[VK_DOWN] = KeyDown;
		KeyMap['W'] = KeyUp;		KeyMap[VK_UP] = KeyUp;
		KeyMap['D'] = KeyRight;		KeyMap[VK_RIGHT] = KeyRight;
		KeyMap['A'] = KeyLeft;		KeyMap[VK_LEFT] = KeyLeft;
		
		KeyMap[VK_PAUSE] = KeyPause;
		KeyMap[VK_END] = KeyEnd;
		KeyMap[VK_HOME] = KeyHome;
		KeyMap[VK_ESCAPE] = KeyEscape;
		KeyMap[VK_RETURN] = KeyReturn;
		KeyMap[VK_SPACE] = KeySpace;
	}

	void Input::Update(void)
	{
		// ************************************************
		// *** Actualizamos los estados de las teclas
		// ************************************************
		MSG msg;

		// Ponemos a 0 los mapas KeyPressed y KeyReleased
		ResetBuffers();

		// Vemos en la cola de mensaje si se han presionado o soltado teclas desde el anterior ciclo
		// PENDIENTE: recuperar y pasar el manejador de ventana
		while( PeekMessage(&msg, NULL, WM_KEYDOWN,WM_KEYUP, PM_REMOVE ) )
		{
			// TranslateMessage(&msg);
			if( (msg.message==WM_KEYUP) || (msg.message==WM_KEYDOWN) )
			{
				switch( msg.message )
				{
					case WM_KEYDOWN:
						OnKeyPressed(msg.wParam,true);
						break;
					case WM_KEYUP:
						OnKeyPressed(msg.wParam,false);
						break;
				}
			}
			else
			{
				DispatchMessage(&msg);
			}
		}

		// ************************************************
		// *** Actualizamos el los estados del rat�n
		// ************************************************
		POINT mousePos;

		static const int middleX = Window::Instance().GetWidth() >> 1;
		static const int middleY = Window::Instance().GetHeight() >> 1;
		
		GetCursorPos(&mousePos);						
		
		dx = (middleX - mousePos.x);
		dy = (middleY - mousePos.y);

		SetCursorPos(middleX, middleY);
	}

	void Input::OnKeyPressed(WPARAM Key, bool Pressed)
	{
		int KeyFunction;

		KeyFunction = KeyMap[LOBYTE(Key)];

		if( KeyFunction == MAX_KEYS )
			return;

		if( KeyState[KeyFunction] != Pressed )
			if( Pressed )
				KeyPressed[KeyFunction] = true;
			else
				KeyReleased[KeyFunction] = true;

		KeyState[KeyFunction] = Pressed;
	}

	void Input::ResetBuffers(void)
	{
		for(short a=0; a<MAX_KEYS; a++)
			KeyPressed[a] = KeyReleased[a] = false;
	}

} // namespace Small