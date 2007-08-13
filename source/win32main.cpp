
#include "win32main.h"

int APIENTRY WinMain( HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow )
{
	// PENDIENTE: implementar un Init()
	Small::Engine::Instance().Run();
	// PENDIENTE: implementar un Destroy()
}
