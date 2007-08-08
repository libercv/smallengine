//////////////////////////////////////////////////////////////////////////////////////////
//	Vector4d.cpp
//	Function definitions for 4d vector class
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	15th August 2002	-	prevent divide by zero in operator Vector3d()
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//////////////////////////////////////////////////////////////////////////////////////////	

#include "maths.h"

namespace Small
{

void Vector4d::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

Vector4d Vector4d::GetRotatedX(double angle) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateX(angle);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}

void Vector4d::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

Vector4d Vector4d::GetRotatedY(double angle) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateY(angle);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}

void Vector4d::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

Vector4d Vector4d::GetRotatedZ(double angle) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateZ(angle);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}

void Vector4d::RotateAxis(double angle, const Vector3d & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}

Vector4d Vector4d::GetRotatedAxis(double angle, const Vector3d & axis) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateAxis(angle, axis);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}


Vector4d operator*(float scaleFactor, const Vector4d & rhs)
{
	return rhs*scaleFactor;
}

bool Vector4d::operator==(const Vector4d & rhs) const
{
	if(x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w)
		return true;

	return false;
}

Vector4d::operator Vector3d()
{
	if(w==0.0f || w==1.0f)
		return Vector3d(x, y, z);
	else
		return Vector3d(x/w, y/w, z/w);
}
}
