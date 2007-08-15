#ifndef DRAWING3D_H
#define DRAWING3D_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "texture.h"
#include "font.h"
#include "../singleton.h"
#include "../math/maths.h"

namespace Small 
{
	class Drawing3D : public Singleton<Drawing3D>
	{
		template<class Drawing3D> friend class Singleton;

	private:
		GLUquadricObj *quadratic;
		int FloorTexture;

		int g_Texture[6];
		static const int BACK_ID = 0;
		static const int FRONT_ID = 1;
		static const int TOP_ID = 2;
		static const int BOTTOM_ID = 3;
		static const int LEFT_ID = 4;
		static const int RIGHT_ID = 5;

	protected:
		Drawing3D(void);
		~Drawing3D(void) {};

	public:
		Font *BigFont;

		void Init(void);

		void DrawAxes(float Length, bool DrawLetters);
		void DrawCamera(float Scale);
		void DrawFloor(void);
		void DrawLight(bool On, float Scale);
		void DrawSkyBox(float x, float y, float z, float width, float height, float length);
		void DrawPoint(void);
		void DrawBox(float x1, float y1, float z1, float x2, float y2, float z2);
		void DrawUnalignedBox(Vector4d Points[8]);
	}; // class Drawing3D
} // namespace Small

#endif // DRAWING3D_H