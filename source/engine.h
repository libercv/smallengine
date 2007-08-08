#ifndef ENGINE_H
#define ENGINE_H

#ifdef WINDOWS
#include <Windows.h>
#endif

#include <iostream>
#include <math.h>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>

#include "game.h"
//#include "system/system.h"
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
	class Engine
	{
	private:
		Engine(void);
		~Engine() {};
		Engine(Engine const&) {};
		Engine &operator=(Engine const&) {};

	public:
		vector<Object>Objects;
		vector<Camera>Cameras;
		vector<Light>Lights;

		// PENDIENTE: propiedades para pruebas
		short iCamera;
		WayMap Map;
		WayPath Path;
		BSP::Q3BSP Bsp;
		BSP::Frustum Frustum;

		static Engine &Instance()
		{
			static Engine oEngine;
			return oEngine;
		}
		
		void Render(void);
		void Update(void);
	};
} // namespace Small
#endif
