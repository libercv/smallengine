#ifndef GAME_H
#define GAME_H

#include "system/window.h"
#include "engine.h"
#include "ui/menu.h"

namespace Small
{
enum GameState{ StateGame, StateMenu, StateDone, StatePause };

class Game
{
private:
	Game(void) { State = StateGame; };
	~Game(void) {};
	Game(Game const&) {};
	Game &operator=(Game const&) {};

public:

	GameState State;

	static Game &Instance()
	{
		static Game oGame;
		return oGame;
	}

	void Run(void);
};

} // namespace Small

#endif //GAME_H
