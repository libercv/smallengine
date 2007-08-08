/*
	Esta es la clase derivada de window para linux
	Tiene lo básico para que pueda trabajar con ella el motor (deriva de IWindow)
	más lo necesario para el manejo de eventos y lo específico de linux
*/
#ifndef WINDOW_H
#define WINDOW_H

#include "iwindow.h"

#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>

namespace Small
{
	class Window:public IWindow
	{
	protected:
		// Propiedades de la ventana
		int screen;
				GLXContext ctx;
		bool fs;
		int x, y;
		unsigned int width, height;
		unsigned int depth;

		// Propiedades del escritorio. Se guardan para restaurarlas al salir
		XF86VidModeModeInfo deskMode; // Modo del escritorio
		XKeyboardState deskKeyboardState; // Estado del teclado en el escritorio
		
		~Window(void) { Close(); };
		Window(Window const&) {};
		Window &operator=(Window const&) {};
	public:
		// Necesario que sea público para el manejo del teclado desde system
		Display *dpy;
		::Window win;

		// Métodos públicos
		bool Open(char *Title, int x, int y, int Width, int Height, int  Depth, bool FullScreen);
		void Close();
		void Refresh(void);
		void Update(void);
		void OnFocusOut(void);
		void OnFocusIn(void);
		void OnResize(int NewWidth, int NewHeight);
		Window(void) {};
		
		static Window &Instance()
		{
			static Window oWindow;
			return oWindow;
		}

		inline int GetWidth(void) { return width; };
		inline int GetHeight(void) { return height; };
	
	};
}
#endif // WINDOW_H
