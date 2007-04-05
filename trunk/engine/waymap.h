
#ifndef WAYMAP_H
#define WAYMAP_H

#ifdef WINDOWS
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
		WayPoint(float NewX, float NewY, float NewZ)
		{
			x = NewX;
			y = NewY;
			z = NewZ;
		}

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
		vector<WayPoint>Points;

		WayPath(void)
		{
			Points.push_back( WayPoint(  0.0f,   0.0f, -240.0f) );
			Points.push_back( WayPoint(900.0f,   0.0f, -240.0f) );
			Points.push_back( WayPoint(900.0f,   0.0f,  670.0f) );
			Points.push_back( WayPoint(900.0f,   0.0f,  670.0f) );
			Points.push_back( WayPoint(  0.0f, 304.0f,  670.0f) );
			Points.push_back( WayPoint(  0.0f, 304.0f, -240.0f) );
			Points.push_back( WayPoint(900.0f, 304.0f, -240.0f) );
			Points.push_back( WayPoint(900.0f, 304.0f,  400.0f) );
			Points.push_back( WayPoint(  0.0f, 304.0f,  400.0f) );
			Points.push_back( WayPoint(  0.0f, 304.0f,  670.0f) );
			Points.push_back( WayPoint(900.0f,   0.0f,  670.0f) );
			Points.push_back( WayPoint(900.0f,   0.0f,  380.0f) );
			Points.push_back( WayPoint(  0.0f,   0.0f,  380.0f) );
		}

		void Render(void)
		{
			bool First=true;
			float lx,ly,lz;

			vector<WayPoint>::iterator WayPointItor;

			glColor3f(1.0f, 0.0f, 0.0f);
			glLineWidth( 10.0f );
			for(WayPointItor=Points.begin(); WayPointItor!=Points.end(); WayPointItor++)
			{
				if( First )
				{
					First = false;
				}
				else
				{
					glBegin( GL_LINES );
						glVertex3f( lx, ly+30.0f, lz );
						glVertex3f( (*WayPointItor).x, (*WayPointItor).y+30.0f, (*WayPointItor).z );
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
} // namespace Small
#endif // WAYMAP_H

