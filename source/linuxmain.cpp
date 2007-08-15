/* 
	Archivo principal del juego para linux.
	Ahora mismo se usa para hacer pruebas.
*/

#include "engine.h"
//#include "../engine/engine.h"
//#include "../engine/ui/menu.h"

using namespace Small;

int main(void)
{

	Small::Engine::Instance().Run();
/*
	System::Instance().UpdateEvents();

	while( Engine::Instance().State != StateDone )
	{
		System::Instance().UpdateEvents();

		switch( Engine::Instance().State )
		{
			case StateMenu:
				Menu::Instance().Update();
				Menu::Instance().Render();
				break;

			case StateGame:
				Engine::Instance().Update();
				Engine::Instance().Render();
				break;
		}

		Small::Window::Instance().Refresh();
	}
*/
	return 0;
} 

