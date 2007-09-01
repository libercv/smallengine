#ifndef STATEGAME_H
#define STATEGAME_H

#ifdef _WIN32
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#endif

// #include <iostream>
#include <math.h>
#include <vector>

#include <GL/gl.h>	// PENDIENTE: no debe haber código OpenGL fuera de Drawing3D salvo que esté muy muy muy justificado
#include <GL/glu.h>

#include "istate.h"
#include "singleton.h"
#include "engine.h" // PENDIENTE: Quitar. stateGame no debe ver a Engine, solo debe devolverle un estado de salida desde stateGame::update.
#include "system/input.h"
#include "graphics/drawing3d.h"
#include "graphics/md2.h"
#include "world/object.h"
#include "world/player.h"
#include "world/camera.h"
#include "world/light.h"
#include "math/maths.h"
#include "waymap.h"
#include "graphics/q3bsp.h"
#include "graphics/frustum.h"

using namespace std;

namespace Small
{
	class StateGame : public Singleton<StateGame>, public IState
	{
		friend class Singleton<StateGame>;

	private:
		int mouse, mouseMask;	// PENDIENTE: esto está aquí de forma temporal

	protected:
		StateGame(void);
		~StateGame() {};

	public:
		vector<Object>Objects;
		vector<Camera>Cameras;
		vector<Light>Lights;
		vector<Player>Players;

		void LoadLevel(void);	// PENDIENTE: pasar un nombre de fichero o un id del nivel.

		// PENDIENTE: propiedades para pruebas
		float dt;
		size_t iCamera;
		WayMap Map;
		WayPath Path;
		BSP::Q3BSP Bsp;
		BSP::Frustum Frustum;
		
		EngineStateEnum Update(float ElapsedTime);
		void Render(void);

		void KillPlayer(void);

#ifdef _WIN32
		void RedirectIOToConsole(void);
#endif
	};
} // namespace Small
#endif

