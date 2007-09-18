
#include "object.h"
#include "../math/maths.h"

namespace Small
{

Object::Object() : Entity()
{
	Model=NULL;
	HotSpot = X_MIDDLE | Y_BOTTOM | Z_MIDDLE;
}

void Object::Update(void)
{
	Entity::Update();
}

void Object::Render(void)
{
	Vector4d BoxPoints[8];
	Matrix4x4 RotationMatrix;

	if( Model )
	{
		// PENDIENTE: crear clase Box3d
		box_t bbox;
		Model->GetInterpolatedBoundingBox( bbox );

		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
			glTranslatef(Position.x, Position.y - bbox[1], Position.z);

			// PENDIENTE: ¿ y este ajuste que hay que hacerle a la rotación ... ?
			// glRotatef(-GetRotationY() + 90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(GetRotationY(), 0.0f, 1.0f, 0.0f);

			// BillboardXZ(View);

			// PENDIENTE: deberíamos recibir el tiempo transcurrido como parámetro y no acceder a Timer
			// PENDIENTE: Model no trabaja con el tiempo transcurrido entre frames sino con el tiempo
			// transcurrido desde el inicio del programa.
			Model->DrawModel(Timer::Instance().GetTime()/1000.0f);

			// Drawing3D::Instance().DrawBox(bbox[0],bbox[1],bbox[2], bbox[3],bbox[4],bbox[5]);
		glPopMatrix();


		/*
		BoxPoints[0].Set(bbox[0], bbox[1], bbox[2], 0);
		BoxPoints[1].Set(bbox[0], bbox[4], bbox[2], 0);
		BoxPoints[2].Set(bbox[3], bbox[4], bbox[2], 0);
		BoxPoints[3].Set(bbox[3], bbox[1], bbox[2], 0);

		BoxPoints[4].Set(bbox[3], bbox[4], bbox[5], 0);
		BoxPoints[5].Set(bbox[3], bbox[1], bbox[5], 0);
		BoxPoints[6].Set(bbox[0], bbox[1], bbox[5], 0);
		BoxPoints[7].Set(bbox[0], bbox[4], bbox[5], 0);

		RotationMatrix.SetRotationEuler(90,0,0);
		for( short a=0; a<7; a++)
		{
			BoxPoints[a] = RotationMatrix.GetRotatedVector3D(BoxPoints[a]);
		}
		

		Drawing3D::Instance().DrawUnalignedBox(BoxPoints);
		*/
		// Drawing3D::Instance().DrawBox(bbox[0],bbox[1],bbox[2], bbox[3],bbox[4],bbox[5]);
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glTranslatef(Position.x, Position.y, Position.z);
			glColor3f(0.0f, 1.0f, 0.0f);
			Drawing3D::Instance().DrawSphere(5.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
		glPopMatrix();
	}
};

void Object::RenderBoundingBox(void)
{
	// PENDIENTE: crear y usar clase Box3D
	/*
	static box_t bbox;
	Vector3d Vertex;

	if( !Model )
		return;

	Model->GetInterpolatedBoundingBox( bbox );
	
	Vertex.x = Position.x - bbox[0];
	Vertex.y = Position.y - bbox[1];
	Vertex.z = Position.z - bbox[2];

	glPushMatrix();
		glTranslatef(Vertex.x, Vertex.y, Vertex.z);
		BillboardXZ(View);
		Drawing3D::Instance().DrawBox(bbox[0],bbox[1],bbox[2], bbox[3],bbox[4],bbox[5]);
	glPopMatrix();
	*/
}

} // namespace Small
