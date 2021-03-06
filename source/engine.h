#ifndef ENGINE_H
#define ENGINE_H

#include "system/window.h"
#include "sound/sound.h"

#include "stategame.h"
#include "statemenu.h"
#include "log.h"

namespace Small
{

class Engine
{
private:
	Engine(void) { CurrentState = Game; };
	~Engine(void) {};
	Engine(Engine const&) {};
	Engine &operator=(Engine const&) {};

public:
	int Level; // PENDIENTE: hacer privada

	EngineStateEnum CurrentState;

	static Engine &Instance()
	{
		static Engine oEngine;
		return oEngine;
	}

	void Run(void);
};

} // namespace Small

#endif // ENGINE_H
