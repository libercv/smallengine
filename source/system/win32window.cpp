
#include "win32window.h"

namespace Small
{

Window::Window(void) : hWnd(NULL), hInstance(NULL)
{ 
	hDC=NULL;
	hRC=NULL;
};

bool Window::Open(char *pTitle, int px, int py, int pWidth, int pHeight, int pColorDepth, bool pFullScreen)
{ 
	RECT WindowRect;
	UINT PixelFormat;	
	DWORD dwStyle, dwExStyle;

	x = px;
	y = py;
	Width = pWidth;
	Height = pHeight;
	ColorDepth = pColorDepth;
	FullScreen = pFullScreen;

	if( !RegisterWindow() )
	{
		Close();
		return false;
	}

	if( FullScreen )
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = Width;
		dmScreenSettings.dmPelsHeight = Height;
		dmScreenSettings.dmBitsPerPel = ColorDepth;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if( ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL )
			return false;

		dwExStyle=WS_EX_APPWINDOW;
		dwStyle=WS_POPUP;
		ShowCursor(false);
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}

	// Ajuste fino del tamaño de la ventana (por los bordes, etc.)
	/*
	WindowRect.top = 0; WindowRect.left = 0;
	WindowRect.right = Width; WindowRect.bottom = Height;
	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);
	*/

	if (!(hWnd=CreateWindowEx( dwExStyle,
								"SmallWindow",
								pTitle,
								dwStyle |
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								x,y,Width,Height,
								NULL,
								NULL,
								//hInstance, // PENDIENTE: guardar la instancia de aplicación
								NULL,
								(void *)this))) // TRUCO: me guardo un puntero al objeto ventana.
	{
		Close();
		return false;
	}

	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		ColorDepth,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	// Obtenemos contexto de dispositivo
	if( !(hDC=GetDC(hWnd)) )
	{
		Close();
		return false;
	}

	// Obtenemos un formato de pixel compatible con el que precisamos
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		Close();
		return false;
	}

	// Establecemos el formato de pixel solicitado
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		Close();
		return false;
	}

	// Obtenemos contexto de render
	if( !(hRC=wglCreateContext(hDC)) )
	{
		Close();
		return false;
	}

	// Activamos la ventana actual para salidas de OpenGL
	if(!wglMakeCurrent(hDC,hRC))					
	{
		Close();
		return false;
	}

	// Mostramos la ventana
	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	// PENDIENTE: quizá este no sea el mejor sitio para inicializar Drawing3D
	// Drawing3D::Instance().Init();
	
	return true;
}

bool Window::RegisterWindow()
{
    WNDCLASSEX wcx; 

	// Definimos el estilo de la ventana
    wcx.cbSize = sizeof(WNDCLASSEX);
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcx.lpfnWndProc = Window::MsgRouter;
    wcx.cbClsExtra = 0;							
    wcx.cbWndExtra = 0;							
	// PENDIENTE: Parece que con wcx.hInstance = NULL sigue funcionando bien ¿¿¿???
    //wcx.hInstance = hInstance;
	wcx.hInstance = NULL;
    wcx.hIcon = LoadIcon(NULL, IDI_WINLOGO);	
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);	
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcx.lpszMenuName = NULL;								
    wcx.lpszClassName = "SmallWindow";						
    wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);			

	// Registramos la nueva clase de ventana
	if (RegisterClassEx(&wcx) == 0)
		return FALSE;
	else
		return TRUE;
}

void Window::Close(void)
{
	if( FullScreen )
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	if( hRC )
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(hRC);
		hRC=NULL;
	}

	if( hDC )
	{
		ReleaseDC(hWnd,hDC);
		hDC=NULL;
	}

	if( hWnd )
	{
		DestroyWindow(hWnd);
		hWnd=NULL;
	}

	if( hInstance )
	{
		UnregisterClass("SmallWindow", hInstance);
		hInstance=NULL;
	}
}

// Enrutador de mensajes
LRESULT CALLBACK Window::MsgRouter(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window *pWnd;

	// ¿ Es el mensaje que anuncia la creación de la ventana ?
	if (uMsg == WM_NCCREATE)
	{
		// Si es así me guardo el puntero al objeto window que encapsula la ventana
		SetWindowLong(hwnd, GWL_USERDATA, (long)((LPCREATESTRUCT(lParam))->lpCreateParams));
	}

	// Objtengo el objeto window al que va encaminado el mensaje
	pWnd = GetObjectFromWindow(hwnd);

	if (pWnd)
		// Si logro identificar el objeto window, le mando el mensaje
		return pWnd->MsgHandler(hwnd, uMsg, wParam, lParam);
	else
		// Si no se lo mando al dispatcher general
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Window::MsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg )
	{
		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0);
			DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;

		case WM_QUIT:
			// PENDIENTE: desde "window" no se debería de ver "game"
			// Game::Instance().State = StateDone;

		case WM_SIZE:
			OnResize(LOWORD(lParam), HIWORD(lParam));			
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void Window::Refresh(void)
{
	SwapBuffers(hDC);
}

void Window::OnResize(int NewWidth, int NewHeight)
{
	if( NewHeight==0 )
		NewHeight=1;

	Width = NewWidth;
	Height = NewHeight;

	glViewport(0,0,Width,Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

}