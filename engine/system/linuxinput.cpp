#include "linuxinput.h"
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>

#include <iostream>

#include "linuxwindow.h"

// Inicialización de input
Input::Input(void)
{
	static const int middleX = Small::Window::Instance().GetWidth() >> 1;
	static const int middleY = Small::Window::Instance().GetHeight() >> 1;

	x= middleX;
	y= middleY;
	dx = dy = 0;

	memset(KeysPressed, false, MAX_KEYS*sizeof(bool));
	
	for (int i=0; i<65535; i++)
		KeysTranslated[i]=MAX_KEYS;

//	memset(KeysTranslated, MAX_KEYS, 65535*sizeof(Keys));
	// Aqui definimos las teclas a usar en el motor
	KeysTranslated[XK_Down] = KeyDown;
	KeysTranslated[XK_Up] = KeyUp;
	KeysTranslated[XK_Right] = KeyRight;
	KeysTranslated[XK_Left] = KeyLeft;
	KeysTranslated[XK_Escape] = KeyEscape;
	KeysTranslated[XK_space] = KeySpace;
	KeysTranslated[XK_Return] = KeyReturn;
	KeysTranslated[XK_Pause] = KeyPause;
	KeysTranslated[XK_End] = KeyEnd;
	KeysTranslated[XK_Home] = KeyHome;
};


// Informa si una tecla ha sido pulsada
bool Input::IsKeyPressed(Keys Key)
{
	return KeysPressed[Key];
};

// Informa si una tecla ha sido soltada
bool Input::IsKeyReleased(Keys Key)
{
	return KeysReleased[Key];
};

// Devuelve el estado de una tecla
bool Input::GetKeyState(Keys Key)
{
	return KeysState[Key];
};

// Devuelve si se ha pulsado un botón del ratón
// FIXME: Por hacer
bool Input::IsMouseButtonPressed(MouseButtons Button)
{
	return false;
};

// Devuelve la posición del ratón
void Input::GetMousePosition(int *outX, int *outY)
{
	*outX = x;
	*outY = y;
};


// Este método recibe un evento de teclado y lo dirige al método adecuado
// que deba encargarse de manejarlo
void Input::OnEvent( void *Event)
{
	XEvent *event = (XEvent *) Event;
	XMotionEvent * motion;
	KeySym key;
		
	switch (event->type)
	{
		case KeyPress:
                	key = XLookupKeysym(&event->xkey, 0);
			if (KeysTranslated[key]!=MAX_KEYS)
				_KeyPressed(KeysTranslated[key], true);
	               	break;
		case KeyRelease:
			key = XLookupKeysym(&event->xkey, 0);
			if (KeysTranslated[key]!=MAX_KEYS)
				_KeyPressed(KeysTranslated[key], false);
			break;
		case MotionNotify:
			motion = (XMotionEvent *) Event;
			break;
	};
}

// Hemos pulsado una tecla
void Input::_KeyPressed(Keys key, bool pressed)
{
	if(KeysState[key]!=pressed)
		if (pressed==true)			
			KeysPressed[key]=true;
		else	
			KeysReleased[key]=true;
		KeysState[key]=pressed;
  
};

// Reinicia (borra) los buffers de teclado
void Input::ResetBuffers(void)
{
	for(short a=0;a<MAX_KEYS;a++)
		KeysPressed[a] = KeysReleased[a] = false;
}

// Actualiza el estado del teclado y ratón
// Para ello filtra los eventos de XWindows referentes al teclado 
// y luego pregunta por el estado del ratón
void Input::Update(void)
{
	XEvent event;

	ResetBuffers();

	// Obtenemos y procesamos los eventos de entrada
	long mascaraInput = PointerMotionMask | KeyReleaseMask | KeyPressMask ; 
	while (XCheckMaskEvent(Small::Window::Instance().dpy,  mascaraInput, &event))
		OnEvent(&event);

	static const int middleX = Small::Window::Instance().GetWidth() >> 1;
	static const int middleY = Small::Window::Instance().GetHeight() >> 1;

	::Window rootReturn, childReturn;
	int root_x_return, root_y_return, win_x_return, win_y_return;
	unsigned int mask_return;

	// Obtenemos el estado del ratón
	XQueryPointer(Small::Window::Instance().dpy, Small::Window::Instance().win, &rootReturn, &childReturn, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return);
	
	dx = ( x - win_x_return);
	dy = ( y - win_y_return);
	
	x = win_x_return;
	y = win_y_return;

	//FIXME: Chapucilla para mantener el ratón dentro de la ventana. Si se pasa de ciertos márgenes, lo centramos
	if( (x > (float)middleX*1.9) || (x<(float)middleX*0.1) || (y<(float)middleY*0.1) || (y>(float)middleY*1.9))
	{
		XWarpPointer(Small::Window::Instance().dpy, Small::Window::Instance().win, Small::Window::Instance().win, 0, 0, 0, 0, middleX, middleY);
		x= middleX;
		y= middleY;
	}
	
}	

// Devuelve lo que se ha movido el ratón desde el último frame
void Input::GetMouseMotion(int *outDx, int *outDy)
{
	*outDx = dx;
	*outDy = dy;
}
