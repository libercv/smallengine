
#include "engine.h"

namespace Small
{
void Engine::Run(void)
{
	// PENDIENTE: Implementar métodos init para todos los singleton.
	// PENDIENTE: Llamar desde aquí a todos los Inits de forma lógica y ordenada.

	Window::Instance().Open("Small Project", 0, 0, 800, 600, 32, false);

	while( CurrentState != State::StateId::Done )
	{
		Timer::Instance().Update();
		Input::Instance().Update();
		Window::Instance().Update();
		//System::Instance().UpdateEvents(); // ¿Esto para qué era?

		switch( CurrentState )
		{
			case State::StateId::Menu:
				CurrentState = StateMenu::Instance().Update(Timer::Instance().GetElapsedTime());
				StateMenu::Instance().Render();
				break;

			case State::StateId::Game:
			case State::StateId::Pause:
				CurrentState = StateGame::Instance().Update(Timer::Instance().GetElapsedTime());
				StateGame::Instance().Render();
				break;
		}

		Window::Instance().Refresh();
	}
}
} // namespace Small
