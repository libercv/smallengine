#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

#include <gl/gl.h>
#include <gl/glu.h>

#include "iwindow.h"
#include "../../game/game.h"

namespace Small
{
	class Window : public IWindow
	{
	private:
		HINSTANCE hInstance;	// Instancia de aplicación
		HDC hDC;				// Manejador de contexto de dispositivo
		HWND hWnd;				// Manejador de la ventana de la aplicación
		HGLRC hRC;				// Manejador de contexto de render (OpenGL)
		WNDPROC msgHandler;

		int x,y, Width, Height, ColorDepth;
		bool FullScreen;

		Window(void);
		~Window(void) { Close(); };
		Window(Window const&) {};
		Window &operator=(Window const&) {};

		bool RegisterWindow(void);

		static LRESULT CALLBACK MsgRouter(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK MsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		inline static Window *GetObjectFromWindow(HWND hWnd)
		{
			return (Window *)GetWindowLong(hWnd, GWL_USERDATA);
		}

		void OnResize(int NewWidth, int NewHeight);

	// Específicas del sistema operativo
	public:
		HDC GetContext(void) { return hDC; }

	public:
		static Window &Instance()
		{
			static Window oWindow;
			return oWindow;
		}

		bool Open(char *Title, int x, int y, int Width, int Height, int Depth, bool FullScreen);
		void Close(void);
		void Refresh(void);
		void Update(void) {};

		inline int GetWidth(void) { return Width; };
		inline int GetHeight(void) { return Height; };
	};

} // namespace Small
#endif

