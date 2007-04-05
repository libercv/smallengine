//////////////////////////////////////////////////////////////////////////////////////////
//	Plane.cpp
//	function definitions for RGBA color class
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	6th August 2002	-	Added "Normalize"
//				7th November 2002	-	Altered constructor layout
//									-	Corrected "lerp"
//////////////////////////////////////////////////////////////////////////////////////////	

#include "maths.h"

namespace Small
{
void Plane::SetFromPoints(const Vector3d & p0, const Vector3d & p1, const Vector3d & p2)
{
	normal=(p1-p0).CrossProduct(p2-p0);

	normal.Normalize();

	CalculateIntercept(p0);
}

void Plane::Normalize()
{
	float normalLength=normal.GetLength();
	normal/=normalLength;
	intercept/=normalLength;
}

bool Plane::Intersect3(const Plane & p2, const Plane & p3, Vector3d & result)//find point of intersection of 3 planes
{
	float denominator=normal.DotProduct((p2.normal).CrossProduct(p3.normal));
											//scalar triple product of normals
	if(denominator==0.0f)									//if zero
		return false;										//no intersection

	Vector3d temp1, temp2, temp3;
	temp1=(p2.normal.CrossProduct(p3.normal))*intercept;
	temp2=(p3.normal.CrossProduct(normal))*p2.intercept;
	temp3=(normal.CrossProduct(p2.normal))*p3.intercept;

	result=(temp1+temp2+temp3)/(-denominator);

	return true;
}

float Plane::GetDistance(const Vector3d & point) const
{
	return point.x*normal.x + point.y*normal.y + point.z*normal.z + intercept;
}

int Plane::ClassifyPoint(const Vector3d & point) const
{
	float distance=point.x*normal.x + point.y*normal.y + point.z*normal.z + intercept;

	if(distance>EPSILON)	//==0.0f is too exact, give a bit of room
		return POINT_IN_FRONT_OF_PLANE;
	
	if(distance<-EPSILON)
		return POINT_BEHIND_PLANE;

	return POINT_ON_PLANE;	//otherwise
}

Plane Plane::lerp(const Plane & p2, float factor)
{
	Plane result;
	result.normal=normal*(1.0f-factor) + p2.normal*factor;
	result.normal.Normalize();

	result.intercept=intercept*(1.0f-factor) + p2.intercept*factor;

	return result;
}

bool Plane::operator ==(const Plane & rhs) const
{
	if(normal==rhs.normal && intercept==rhs.intercept)
		return true;

	return false;
}
}
