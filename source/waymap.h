
#ifndef WAYMAP_H
#define WAYMAP_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>

#include "math/vector3d.h"
#include "graphics/drawing3d.h"

using namespace std;

namespace Small
{
	class WayPoint : public Vector3d
	{
	public:
		// PENDIENTE: cambiar por un Vector3d
		WayPoint(float NewX, float NewY, float NewZ)
		{
			x = NewX;
			y = NewY;
			z = NewZ;
		}

		// PENDIENTE: llevar a Drawing3D (Drawing3D::Instance().DrawPoint(this);)
		void Render(void)
		{
			glPushMatrix();
			{
				glTranslatef(x, y, z);
				Drawing3D::Instance().DrawPoint();
			}
			glPopMatrix();
		}
	};

	class WayPath
	{
	public:
		std::string Id;
		vector<WayPoint>Points;

		WayPath(void)
		{
		}

		// PENDIENTE: llevar a Drawing3D (Drawing3D::Instance().DrawPath(this);)
		void Render(void)
		{
			bool First=true;
			float lx,ly,lz;

			vector<WayPoint>::iterator WayPointItor;

			glColor3f(1.0f, 0.0f, 0.0f);
			glLineWidth( 2.0f );
			for(WayPointItor=Points.begin(); WayPointItor!=Points.end(); WayPointItor++)
			{
				if( First )
				{
					First = false;
				}
				else
				{
					glBegin( GL_LINES );
						glVertex3f( lx, ly+1.0f, lz );
						glVertex3f( (*WayPointItor).x, (*WayPointItor).y+1.0f, (*WayPointItor).z );
					glEnd();
				}

				(*WayPointItor).Render();

				lx = (*WayPointItor).x;
				ly = (*WayPointItor).y;
				lz = (*WayPointItor).z;
			}
		}

		size_t Count(void)
		{
			return Points.size();
		}

		void Update(void) {};
	};


	/*
		PENDIENTE: WayMap tiene que ser un grafo con nodos interconectados a través del cual poder calcular
		un path mediante A* para llegar de un punto a otro del mapa esquivando obstáculos.
	*/
	class WayMap
	{
	private:
		vector<WayPoint>Points;

	public:

		WayMap(void)
		{
			float x,z;

			for( x=-9.5f; x<10.5f; x++)
			{
				for( z=-9.5f; z<10.5f; z++)
				{
					Points.push_back( WayPoint(x,0.0f,z) );
				}
			}
		}

		void Render(void)
		{
			vector<WayPoint>::iterator WayPointItor;

			glColor3f(0.0f, 1.0f, 0.0f);
			for(WayPointItor=Points.begin(); WayPointItor!=Points.end(); WayPointItor++)
				(*WayPointItor).Render();
		}

		void Update(void) {};
	};

	// PENDIENTE: falta implementar una clase WayExplorer capaz de seguir un WayPath. Las clases
	// que necesiten seguir un path pueden heredar de WayExplorer.

} // namespace Small
#endif // WAYMAP_H

