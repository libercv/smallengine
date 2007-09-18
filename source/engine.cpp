
#include "engine.h"

#include "script/script.h"

namespace Small
{
void Engine::Run(void)
{
	// PENDIENTE: Implementar métodos init para todos los singleton.
	// PENDIENTE: Llamar desde aquí a todos los Inits de forma lógica y ordenada.

	Level = 1;

	// PENDIENTE: si en fullscreen indicamos una resolución que no se puede activar -> excepcion
	Window::Instance().Open("Small Project", 0, 0, 1024, 768, 32, true);

	StateGame::Instance().LoadLevel("level001.xml");

	Script::Instance();	// PENDIENTE: ñapa para forzar la inicialización. 

	while( CurrentState != Done )
	{
		Timer::Instance().Update();
		Input::Instance().Update();
		Window::Instance().Update();
		SoundManager::Instance().Update();

		// PENDIENTE: UpdateEvents se supone que era el que generaba los eventos en LUA 
		// para que el código no estuviese por ahí disperso. Revisar la idea.
		//System::Instance().UpdateEvents();
		switch( CurrentState )
		{
			case Menu:
				CurrentState = StateMenu::Instance().Update(Timer::Instance().GetElapsedTime());
				StateMenu::Instance().Render();
				break;

			case NextLevel:
				if( ++Level > 2 )
					Level = 1;

				switch( Level )
				{
					case 2:
						StateGame::Instance().LoadLevel("level002.xml");
						StateGame::Instance().CrearBolitas();
						break;

					default:
						StateGame::Instance().LoadLevel("level001.xml");
						break;
				}

				CurrentState = Game;
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
