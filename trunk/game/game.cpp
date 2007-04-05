
#include "game.h"

namespace Small
{

void Game::Run(void)
{
	// PENDIENTE: Implementar métodos init para todos los singleton.
	// PENDIENTE: Llamar desde aquí a todos los Inits de forma lógica y ordenada.

	Window::Instance().Open("Small Project",0,0,640,480,16,true);

	while( State != StateDone )
	{
		//System::Instance().UpdateEvents();
		Timer::Instance().Update();
		Input::Instance().Update();
		Window::Instance().Update();

		switch( State )
		{
			case StateMenu:
				Menu::Instance().Update();
				Menu::Instance().Render();
				break;

			case StateGame:
			case StatePause:
				Engine::Instance().Update();
				Engine::Instance().Render();
				break;
		}

		Window::Instance().Refresh();
	}
}
} // namespace Small
