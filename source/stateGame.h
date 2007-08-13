#ifndef STATEGAME_H
#define STATEGAME_H

#ifdef _WIN32
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#endif

#include <iostream>
#include <math.h>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>

#include "state.h"

#include "engine.h" // Quitar. stateGame no debe ver a Engine, solo debe devolverle un estado de salida desde stateGame::update.
#include "system/input.h"
#include "graphics/drawing3d.h"
#include "graphics/md2.h"
#include "world/object.h"
#include "world/camera.h"
#include "world/light.h"
#include "math/maths.h"
#include "waymap.h"

// BSP
#include "graphics/q3bsp.h"
#include "graphics/frustum.h"

using namespace std;

namespace Small
{
	class StateGame : State
	{
	private:
		StateGame(void);
		~StateGame() {};
		StateGame(StateGame const&) {};
		StateGame &operator=(StateGame const&) {};

	public:
		vector<Object>Objects;
		vector<Camera>Cameras;
		vector<Light>Lights;

		// PENDIENTE: propiedades para pruebas
		float dt;
		short iCamera;
		WayMap Map;
		WayPath Path;
		BSP::Q3BSP Bsp;
		BSP::Frustum Frustum;

		static StateGame &Instance()
		{
			static StateGame oStateGame;
			return oStateGame;
		}
		
		void Render(void);
		StateId Update(float ElapsedTime);

#ifdef _WIN32
		void RedirectIOToConsole(void);
#endif
	};
} // namespace Small
#endif
