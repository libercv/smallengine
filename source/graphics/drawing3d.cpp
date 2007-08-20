
#include "drawing3d.h"
#include "../math/maths.h"
#include "../system/window.h"

namespace Small
{
	Drawing3D::Drawing3D(void)
	{
	/*
		FloorTexture = CTextureManager::GetInstance()->LoadTexture("resources/textures/suelo.bmp");

		g_Texture[BACK_ID] = CTextureManager::GetInstance()->LoadTexture("resources/textures/back.bmp");
		g_Texture[FRONT_ID] = CTextureManager::GetInstance()->LoadTexture("resources/textures/front.bmp");
		g_Texture[LEFT_ID] = CTextureManager::GetInstance()->LoadTexture("resources/textures/left.bmp");
		g_Texture[RIGHT_ID] = CTextureManager::GetInstance()->LoadTexture("resources/textures/right.bmp");
		g_Texture[TOP_ID] = CTextureManager::GetInstance()->LoadTexture("resources/textures/top.bmp");
		g_Texture[BOTTOM_ID] = CTextureManager::GetInstance()->LoadTexture("resources/textures/bottom.bmp");

	*/
		BigFont = new Font();

		quadratic=gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluQuadricTexture(quadratic, GL_TRUE);
	}

	/*
		Drawing3D::Init Inicializaci� por defecto de OpenGL
	*/
	void Drawing3D::Init(void)
	{
		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glDepthMask( GL_TRUE );

		glEnable( GL_CULL_FACE );
		glCullFace( GL_BACK );
		glFrontFace( GL_CCW );

		glEnable(GL_TEXTURE_2D);
	}

	void Drawing3D::DrawFloor(void)
	{
		glBindTexture(GL_TEXTURE_2D, FloorTexture);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

			glColor4f(1.0f,1.0f,1.0f,0.3f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_QUADS);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f,0.0f); glVertex3f(-10.0f, 0.0f, -10.0f);
				glTexCoord2f(10.0f,0.0f); glVertex3f( 10.0f, 0.0f, -10.0f);
				glTexCoord2f(10.0f,10.0f); glVertex3f( 10.0f, 0.0f,  10.0f);
				glTexCoord2f(0.0f,10.0f); glVertex3f(-10.0f, 0.0f,  10.0f);
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Drawing3D::DrawAxes(float Length, bool DrawLetters)
	{
		float i=0.0f;

		// Pintamos el suelo
		glLineWidth(2.0f);

		glBegin(GL_LINES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.001f, 0.0f);
			glVertex3f(Length, 0.001f, 0.0f);

			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.001f, 0.0f);
			glVertex3f(0.0f, Length, 0.0f);

			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f, 0.001f, 0.0f);
			glVertex3f(0.0f, 0.001f, Length);
		glEnd();

		if( DrawLetters )
		{
			glColor3f(1.0f,0.0f,0.0f);
			glRasterPos3f(Length, 0.0f, 0.0f);
			Drawing3D::Instance().BigFont->Print("X");

			glColor3f(0.0f,1.0f,0.0f);
			glRasterPos3f(0.0f, Length, 0.0f);
			Drawing3D::Instance().BigFont->Print("Y");

			glColor3f(0.0f,0.0f,1.0f);
			glRasterPos3f(0.0f, 0.0f, Length);
			Drawing3D::Instance().BigFont->Print("Z");
		}

		glLineWidth(1.0f);
	}

	void Drawing3D::DrawCamera(float scale)
	{
		float Width,Height,Depth;
		short mode;

		mode = GL_POLYGON;
		Width = 0.5f * scale;
		Height = 0.5f * scale;
		Depth = 1.0f * scale;

		glColor3f(0.4f, 0.4f, 0.4f);

		// Objetivo (cilindro)
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, 0.7f * scale);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(quadratic, 0.15f * scale, 0.15f * scale, 0.5f * scale, 10, 32);
		glPopMatrix();

		// Cubo
		// front of cube 
		glBegin(mode);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-Width/2, Height/2, Depth/2);
			glVertex3f(-Width/2, -Height/2, Depth/2);
			glVertex3f(Width/2, -Height/2, Depth/2);
			glVertex3f(Width/2, Height/2, Depth/2);
		glEnd();

		// top of cube 
		glBegin(mode);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(Width/2, Height/2, -Depth/2);
			glVertex3f(-Width/2, Height/2, -Depth/2);
			glVertex3f(-Width/2, Height/2, Depth/2);
			glVertex3f(Width/2, Height/2, Depth/2);
		glEnd();

		// left side of cube 
		glBegin(mode);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-Width/2, Height/2, -Depth/2);
			glVertex3f(-Width/2, -Height/2, -Depth/2);
			glVertex3f(-Width/2, -Height/2, Depth/2);
			glVertex3f(-Width/2, Height/2, Depth/2);
		glEnd();

		// bottom of cube 
		glBegin(mode);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(Width/2, -Height/2, -Depth/2);
			glVertex3f(Width/2, -Height/2, Depth/2);
			glVertex3f(-Width/2, -Height/2, Depth/2);
			glVertex3f(-Width/2, -Height/2, -Depth/2);
		glEnd();

		// back of cube 
		glBegin(mode);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(Width/2, Height/2, -Depth/2);
			glVertex3f(Width/2, -Height/2, -Depth/2);
			glVertex3f(-Width/2, -Height/2, -Depth/2);
			glVertex3f(-Width/2, Height/2, -Depth/2);
		glEnd();

		// right side of cube 
		glBegin(mode);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(Width/2, Height/2, Depth/2);
			glVertex3f(Width/2, -Height/2, Depth/2);
			glVertex3f(Width/2, -Height/2, -Depth/2);
			glVertex3f(Width/2, Height/2, -Depth/2);
		glEnd();
	}

	void Drawing3D::DrawLight(bool On, float scale)
	{
		float Radio;
		short mode;

		mode = GL_POLYGON;

		Radio = 1 * scale;

		// bombilla
		if( On )
			glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
		else
			glColor4f(0.3f, 0.3f, 0.3f, 0.5f);

		glPushAttrib( GL_LIGHTING_BIT );
		{
			glDisable(GL_LIGHTING);

			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.0f);
				gluSphere(quadratic,Radio,10,32);
			glPopMatrix();

			//
			// casquillo
			//

			// Casquillo (cilindro)
			glColor3f(0.7f, 0.7f, 0.7f);
			glPushMatrix();
				glTranslatef(0.0f, Radio*1.6f, 0.0f);
				glRotatef(90,  1.0f, 0.0f, 0.0f);
				gluCylinder(quadratic,Radio/2,Radio/2,Radio,10,32);
			glPopMatrix();

			// Casquillo (tapa)
			glPushMatrix();
				glTranslatef(0.0f, Radio*1.5f, 0.0f);
				gluSphere(quadratic,Radio/2.0f,10,32);
			glPopMatrix();
		}
		glPopAttrib();
	}


	void Drawing3D::DrawSkyBox(float x, float y, float z, float width, float height, float length)
	{
		x = x - width  / 2;
		//y = y - height / 2;
		z = z - length / 2;

		glPushAttrib( GL_LIGHTING_BIT );
		{
			glDisable( GL_LIGHTING );

			glBindTexture(GL_TEXTURE_2D, g_Texture[BACK_ID]);
			glBegin(GL_QUADS);		
				glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z); 
				glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y + height, z);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, g_Texture[FRONT_ID]);
			glBegin(GL_QUADS);	
				glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y,			z + length);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y + height, z + length);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
				glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y,			z + length);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, g_Texture[BOTTOM_ID]);
			glBegin(GL_QUADS);		
				glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y,			z);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z + length);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z + length); 
				glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y,			z);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, g_Texture[TOP_ID]);
			glBegin(GL_QUADS);		
				glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
				glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height,	z + length);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y + height,	z);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, g_Texture[LEFT_ID]);
			glBegin(GL_QUADS);		
				glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y,			z);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height,	z + length); 
				glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height,	z);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, g_Texture[RIGHT_ID]);
			glBegin(GL_QUADS);		
				glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y + height,	z);	
				glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y + height,	z + length); 
				glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y,			z);		
			glEnd();
		}
		glPopAttrib();
	}

	void Drawing3D::DrawPoint(void)
	{
		gluSphere(quadratic,0.05f,5,5);
	}

	void Drawing3D::DrawBox(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		// dibujamos el bounding box
		/*
		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		*/

		glColor4f( 0.3f, 0.3f, 1.0f, 0.3f);

		// cara trasera
		glBegin( GL_QUADS );
			glVertex3f( x1, y2, z1);
			glVertex3f( x2, y2, z1);
			glVertex3f( x2, y1, z1);
			glVertex3f( x1, y1, z1);
		glEnd();

		// cara frontal
		glBegin( GL_QUADS );
			glVertex3f( x1, y1, z2);
			glVertex3f( x2, y1, z2);
			glVertex3f( x2, y2, z2);
			glVertex3f( x1, y2, z2);
		glEnd();

		
		// cara izquierda
		glBegin( GL_QUADS );
			glVertex3f( x2, y1, z1);
			glVertex3f( x2, y2, z1);
			glVertex3f( x2, y2, z2);
			glVertex3f( x2, y1, z2);
		glEnd();

		// cara derecha
		glBegin( GL_QUADS );
			glVertex3f( x1, y1, z2);
			glVertex3f( x1, y2, z2);
			glVertex3f( x1, y2, z1);
			glVertex3f( x1, y1, z1);
		glEnd();

		// cara superior
		glBegin( GL_QUADS );
			glVertex3f( x2, y2, z2);
			glVertex3f( x2, y2, z1);
			glVertex3f( x1, y2, z1);
			glVertex3f( x1, y2, z2);
		glEnd();

		// cara inferior
		glBegin( GL_QUADS );
			glVertex3f( x1, y1, z2);
			glVertex3f( x1, y1, z1);
			glVertex3f( x2, y1, z1);
			glVertex3f( x2, y1, z2);
		glEnd();

		/*
		glDisable( GL_BLEND );
		*/
	}

	void Drawing3D::DrawUnalignedBox(Vector4d Points[8])
	{
		// dibujamos el bounding box
		/*
		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		*/

		glColor4f( 0.3f, 0.3f, 1.0f, 0.3f);

		// cara frontal
		glBegin( GL_QUADS );
			glVertex3f( Points[0].GetX(), Points[0].GetY(), Points[0].GetX());
			glVertex3f( Points[1].GetX(), Points[1].GetY(), Points[1].GetX());
			glVertex3f( Points[2].GetX(), Points[2].GetY(), Points[2].GetX());
			glVertex3f( Points[3].GetX(), Points[3].GetY(), Points[3].GetX());
		glEnd();

		// cara trasera
		glBegin( GL_QUADS );
			glVertex3f( Points[4].GetX(), Points[4].GetY(), Points[4].GetX());
			glVertex3f( Points[5].GetX(), Points[5].GetY(), Points[5].GetX());
			glVertex3f( Points[6].GetX(), Points[6].GetY(), Points[6].GetX());
			glVertex3f( Points[7].GetX(), Points[7].GetY(), Points[7].GetX());
		glEnd();
		
		/*
		// cara izquierda
		glBegin( GL_QUADS );
			glVertex3f( x2, y1, z1);
			glVertex3f( x2, y2, z1);
			glVertex3f( x2, y2, z2);
			glVertex3f( x2, y1, z2);
		glEnd();

		// cara derecha
		glBegin( GL_QUADS );
			glVertex3f( x1, y1, z2);
			glVertex3f( x1, y2, z2);
			glVertex3f( x1, y2, z1);
			glVertex3f( x1, y1, z1);
		glEnd();

		// cara superior
		glBegin( GL_QUADS );
			glVertex3f( x2, y2, z2);
			glVertex3f( x2, y2, z1);
			glVertex3f( x1, y2, z1);
			glVertex3f( x1, y2, z2);
		glEnd();

		// cara inferior
		glBegin( GL_QUADS );
			glVertex3f( x1, y1, z2);
			glVertex3f( x1, y1, z1);
			glVertex3f( x2, y1, z1);
			glVertex3f( x2, y1, z2);
		glEnd();
		*/
	}

void Drawing3D::OrthoMode(int left, int top, int right, int bottom)
{
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();								
	glOrtho(left, right, bottom, top, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);								
	glLoadIdentity();
}

void Drawing3D::PerspectiveMode(float AngleOfVision, int WindowWidth, int WindowHeight, float NearPlane, float FarPlane)
{
	glMatrixMode( GL_PROJECTION );							
	glLoadIdentity();
	gluPerspective(AngleOfVision, (GLfloat)WindowWidth / (GLfloat)WindowHeight, NearPlane, FarPlane);

	glMatrixMode( GL_MODELVIEW );							
	glLoadIdentity();
}

} // namespace Small
