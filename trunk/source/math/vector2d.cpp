//////////////////////////////////////////////////////////////////////////////////////////
//	Vector2d.cpp
//	Function definitions for 2d vector class
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	8th November 2002
//////////////////////////////////////////////////////////////////////////////////////////	

#include "vector2d.h"
namespace Small
{

void Vector2d::Normalize()
{
	float length;
	float scalefactor;
	length=GetLength();

	if(length==1 || length==0)			//return if length is 1 or 0
		return;

	scalefactor = 1.0f/length;
	x *= scalefactor;
	y *= scalefactor;
}

Vector2d Vector2d::GetNormalized() const
{
	Vector2d result(*this);

	result.Normalize();

	return result;
}

Vector2d operator*(float scaleFactor, const Vector2d & rhs)
{
	return rhs*scaleFactor;
}

bool Vector2d::operator==(const Vector2d & rhs) const
{
	if(x==rhs.x && y==rhs.y)
		return true;

	return false;
}
}


