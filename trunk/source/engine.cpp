
#include "engine.h"

namespace Small
{
void Engine::Run(void)
{
	// PENDIENTE: Implementar métodos init para todos los singleton.
	// PENDIENTE: Llamar desde aquí a todos los Inits de forma lógica y ordenada.

	// PENDIENTE: si en fullscreen indicamos una resolución que no se puede activar -> excepcion
	Window::Instance().Open("Small Project", 0, 0, 800, 600, 32, false);

	StateGame::Instance().LoadLevel();

	while( CurrentState != Done )
	{
		Timer::Instance().Update();
		Input::Instance().Update();
		Window::Instance().Update();
		SoundManager::Instance().Update();

		//System::Instance().UpdateEvents(); // ¿Esto para qué era?

		switch( CurrentState )
		{
			case Menu:
				CurrentState = StateMenu::Instance().Update(Timer::Instance().GetElapsedTime());
				StateMenu::Instance().Render();
				break;

			case Game:
			case Pause:
				CurrentState = StateGame::Instance().Update(Timer::Instance().GetElapsedTime());
				StateGame::Instance().Render();
				break;
		}

		Window::Instance().Refresh();
	}
}
} // namespace Small
