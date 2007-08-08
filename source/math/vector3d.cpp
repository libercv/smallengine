//////////////////////////////////////////////////////////////////////////////////////////
//	Vector3d.cpp
//	Function definitions for 3d vector class
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//				17th December 2002	-	Converted from radians to degrees
//////////////////////////////////////////////////////////////////////////////////////////	

#include "maths.h"

namespace Small
{

void Vector3d::Normalize(void)
{
	float length=GetLength();

	if(length==1 || length==0)			//return if length is 1 or 0
		return;

	float scalefactor = 1.0f/length;
	x *= scalefactor;
	y *= scalefactor;
	z *= scalefactor;
}

Vector3d Vector3d::GetNormalized() const
{
	Vector3d result(*this);

	result.Normalize();

	return result;
}

Vector3d Vector3d::GetRotatedX(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);

	return Vector3d(	x,
						y*cosAngle - z*sinAngle,
						y*sinAngle + z*cosAngle);
}

void Vector3d::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

Vector3d Vector3d::GetRotatedY(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);

	return Vector3d(	x*cosAngle + z*sinAngle,
						y,
						-x*sinAngle + z*cosAngle);
}

void Vector3d::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

Vector3d Vector3d::GetRotatedZ(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	
	return Vector3d(x*cosAngle - y*sinAngle,
					x*sinAngle + y*cosAngle,
					z);
}

void Vector3d::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

Vector3d Vector3d::GetRotatedAxis(double angle, const Vector3d & axis) const
{
	if(angle==0.0)
		return (*this);

	Vector3d u=axis.GetNormalized();

	Vector3d rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	float oneMinusCosAngle=1.0f-cosAngle;

	rotMatrixRow0.x=(u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
	rotMatrixRow0.y=(u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
	rotMatrixRow0.z=(u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;

	rotMatrixRow1.x=(u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
	rotMatrixRow1.y=(u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
	rotMatrixRow1.z=(u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;
	
	rotMatrixRow2.x=(u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
	rotMatrixRow2.y=(u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
	rotMatrixRow2.z=(u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));

	return Vector3d(	this->DotProduct(rotMatrixRow0),
						this->DotProduct(rotMatrixRow1),
						this->DotProduct(rotMatrixRow2));
}

void Vector3d::RotateAxis(double angle, const Vector3d & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}


void Vector3d::PackTo01()
{
	(*this)=GetPackedTo01();	
}

Vector3d Vector3d::GetPackedTo01() const
{
	Vector3d temp(*this);

	temp.Normalize();

	temp=temp*0.5f+Vector3d(0.5f, 0.5f, 0.5f);
	
	return temp;
}

Vector3d operator*(float scaleFactor, const Vector3d & rhs)
{
	return rhs*scaleFactor;
}

bool Vector3d::operator==(const Vector3d & rhs) const
{
	if(x==rhs.x && y==rhs.y && z==rhs.z)
		return true;

	return false;
}

}
