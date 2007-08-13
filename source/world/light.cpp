
#include "light.h"

namespace Small
{

int Light::LIGHT_NAME_CNT = 0x4000;

Light::Light(void)
{
	On = true;
	LIGHT_NAME = Light::LIGHT_NAME_CNT++;

	/*
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(LIGHT_NAME, GL_DIFFUSE, LightDiffuse);

	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(LIGHT_NAME, GL_AMBIENT, LightAmbient);

	GLfloat LightSpecular[]= { 1.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(LIGHT_NAME, GL_SPECULAR, LightSpecular);
	*/
}

void Light::Render(void)
{
	glPushMatrix();
		glTranslatef(Position.x,Position.y,Position.z);
		// LookAt(ToX,ToY,ToZ);
		Drawing3D::Instance().DrawLight(On, 10);
	glPopMatrix();
}

void Light::Update(void)
{
	Entity::Update();

	if( On )
	{
		GLfloat LightPosition[]= { Position.x, Position.y, Position.z, 1.0f };
		glLightfv(LIGHT_NAME, GL_POSITION, LightPosition);
		glEnable(LIGHT_NAME);
	}
	else
	{
		glDisable(LIGHT_NAME);
	}
}

} // namespace Small
