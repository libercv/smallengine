#ifndef ENGINE_H
#define ENGINE_H

#include "system/window.h"

#include "stateGame.h"
#include "ui/stateMenu.h"

namespace Small
{

class Engine
{
private:
	Engine(void) { CurrentState = State::StateId::Game; };
	~Engine(void) {};
	Engine(Engine const&) {};
	Engine &operator=(Engine const&) {};

public:
	State::StateId CurrentState;

	static Engine &Instance()
	{
		static Engine oEngine;
		return oEngine;
	}

	void Run(void);
};

} // namespace Small

#endif // ENGINE_H
