
#include "win32input.h"

namespace Small
{
	Input::Input(void)
	{
		ResetBuffers();

		// PENDIENTE: sacar la configuración de teclas de un archivo.
		// PENDIENTE: ademas de sacar la configuracion de las teclas a un archivo hay que sacar este codigo de aqui.
		// Lo mas probable es que acabe estando en el engine, en el proceso de carga inicial.
		memset(KeyMap, MAX_KEYS, 256);

		KeyMap['S'] = P1KeyDown;		KeyMap[VK_DOWN] = P2KeyDown;
		KeyMap['W'] = P1KeyUp;			KeyMap[VK_UP] = P2KeyUp;
		KeyMap['D'] = P1KeyRight;		KeyMap[VK_RIGHT] = P2KeyRight;
		KeyMap['A'] = P1KeyLeft;		KeyMap[VK_LEFT] = P2KeyLeft;
		KeyMap['A'] = P1KeyLeft;		KeyMap[VK_LEFT] = P2KeyLeft;
		KeyMap[VK_TAB] = P1KeyJump;		KeyMap[VK_CONTROL] = P2KeyJump;
		
		KeyMap[VK_PAUSE] = KeyPause;
		KeyMap[VK_END] = KeyEnd;
		KeyMap[VK_HOME] = KeyHome;
		KeyMap[VK_ESCAPE] = KeyEscape;
		KeyMap[VK_RETURN] = KeyReturn;
		KeyMap[VK_PRIOR] = KeyPgUp;
		KeyMap[VK_NEXT] = KeyPgDown;
		KeyMap[VK_INSERT] = KeyInsert;
		KeyMap[VK_DELETE] = KeySupr;

		x = y = dx = dy = 0;
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
		// *** Actualizamos los estados del ratón
		// ************************************************
		POINT mousePos;

		static const int middleX = Window::Instance().GetWidth() >> 1;
		static const int middleY = Window::Instance().GetHeight() >> 1;
		
		GetCursorPos(&mousePos);						
		
		dx = (mousePos.x - middleX);
		dy = (mousePos.y - middleY);

		x += dx;
		y += dy;

		if( x>Window::Instance().GetWidth() ) x=Window::Instance().GetWidth();
		if( x<0 ) x=0;

		if( y>Window::Instance().GetHeight() ) y=Window::Instance().GetHeight();
		if( y<0 ) y=0;

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
