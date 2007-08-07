
#include "object.h"
#include "../math/maths.h"

namespace Small
{

Object::Object() : Entity()
{
	Model=NULL;
	HotSpot = X_MIDDLE | Y_BOTTOM | Z_MIDDLE;
	kk=0;
}

void Object::Update(void)
{
	Entity::Update();

	kk += (Timer::Instance().GetElapsedTime()) / 1000.0f;
}

void Object::Render(void)
{
	Vector4d BoxPoints[8];
	Matrix4x4 RotationMatrix;

	if( Model )
	{
		// PENDIENTE: crear clase Box3d
		//box_t bbox;
		//Model->GetInterpolatedBoundingBox( bbox );

		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
			//glTranslatef(Position.x, Position.y - bbox[1], Position.z);
			BillboardXZ(View);
			Model->DrawModel(kk);
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

		//RotationMatrix.SetRotationEuler(90,0,0);
		//for( short a=0; a<7; a++)
		//{
		//	BoxPoints[a] = RotationMatrix.GetRotatedVector3D(BoxPoints[a]);
		//}
		
		Drawing3D::Instance().DrawUnalignedBox(BoxPoints);
		*/
		// Drawing3D::Instance().DrawBox(bbox[0],bbox[1],bbox[2], bbox[3],bbox[4],bbox[5]);
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
