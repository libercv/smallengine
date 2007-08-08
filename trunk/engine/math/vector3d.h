//////////////////////////////////////////////////////////////////////////////////////////
//	Vector3d.h
//	Class declaration for a 3d vector
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//				7th January 2003	-	Added QuadraticInterpolate
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>

namespace Small
{
class Vector3d
{
public:
	//constructors
	Vector3d(void)	:	x(0.0f), y(0.0f), z(0.0f)
	{}

	Vector3d(float newX, float newY, float newZ)	:	x(newX), y(newY), z(newZ)
	{}

	Vector3d(const float * rhs)	:	x(*rhs), y(*(rhs+1)), z(*(rhs+2))
	{}

	Vector3d(const Vector3d & rhs)	:	x(rhs.x), y(rhs.y), z(rhs.z)
	{}

	~Vector3d() {}	//empty

	void Set(float newX, float newY, float newZ)
	{	x=newX;	y=newY;	z=newZ;	}
	
	//Accessors kept for compatibility
	void SetX(float newX) {x = newX;}
	void SetY(float newY) {y = newY;}
	void SetZ(float newZ) {z = newZ;}

	float GetX() const {return x;}	//public accessor functions
	float GetY() const {return y;}	//inline, const
	float GetZ() const {return z;}

	void LoadZero(void)
	{	x=y=z=0.0f;	}
	void LoadOne(void)
	{	x=y=z=1.0f;	}
	
	//vector algebra
	
	Vector3d CrossProduct(const Vector3d & rhs) const
	{	return Vector3d(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);	}

	float DotProduct(const Vector3d & rhs) const
	{	return x*rhs.x + y*rhs.y + z*rhs.z;	}
	
	void Normalize(void);
	Vector3d GetNormalized() const;
	
	float GetLength() const
	{	return (float)sqrt((x*x)+(y*y)+(z*z));	}
	
	float GetSquaredLength() const
	{	return (x*x)+(y*y)+(z*z);	}

	//rotations
	void RotateX(double angle);
	Vector3d GetRotatedX(double angle) const;
	void RotateY(double angle);
	Vector3d GetRotatedY(double angle) const;
	void RotateZ(double angle);
	Vector3d GetRotatedZ(double angle) const;
	void RotateAxis(double angle, const Vector3d & axis);
	Vector3d GetRotatedAxis(double angle, const Vector3d & axis) const;

	//pack to [0,1] for color
	void PackTo01();
	Vector3d GetPackedTo01() const;

	//linear interpolate
	Vector3d lerp(const Vector3d & v2, float factor) const
	{	return (*this)*(1.0f-factor) + v2*factor;	}

	Vector3d QuadraticInterpolate(const Vector3d & v2, const Vector3d & v3, float factor) const
	{	return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;}


	//overloaded operators
	//binary operators
	Vector3d operator+(const Vector3d & rhs) const
	{	return Vector3d(x + rhs.x, y + rhs.y, z + rhs.z);	}
	
	Vector3d operator-(const Vector3d & rhs) const
	{	return Vector3d(x - rhs.x, y - rhs.y, z - rhs.z);	}

	Vector3d operator*(const float rhs) const
	{	return Vector3d(x*rhs, y*rhs, z*rhs);	}
	
	Vector3d operator/(const float rhs) const
	{	return (rhs==0.0f) ? Vector3d(0.0f, 0.0f, 0.0f) : Vector3d(x / rhs, y / rhs, z / rhs);	}

	//multiply by a float, eg 3*v
	friend Vector3d operator*(float scaleFactor, const Vector3d & rhs);

	//Add, subtract etc, saving the construction of a temporary
	void Add(const Vector3d & v2, Vector3d & result)
	{
		result.x=x+v2.x;
		result.y=y+v2.y;
		result.z=z+v2.z;
	}

	void Subtract(const Vector3d & v2, Vector3d & result)
	{
		result.x=x-v2.x;
		result.y=y-v2.y;
		result.z=z-v2.z;
	}

	bool operator==(const Vector3d & rhs) const;
	bool operator!=(const Vector3d & rhs) const
	{	return !((*this)==rhs);	}

	//self-add etc
	void operator+=(const Vector3d & rhs)
	{	x+=rhs.x;	y+=rhs.y;	z+=rhs.z;	}

	void operator-=(const Vector3d & rhs)
	{	x-=rhs.x;	y-=rhs.y;	z-=rhs.z;	}

	void operator*=(const float rhs)
	{	x*=rhs;	y*=rhs;	z*=rhs;	}
	
	void operator/=(const float rhs)
	{	if(rhs==0.0f)
			return;
		else
		{	x/=rhs; y/=rhs; z/=rhs;	}
	}


	//unary operators
	Vector3d operator-(void) const {return Vector3d(-x, -y, -z);}
	Vector3d operator+(void) const {return *this;}

	//cast to pointer to a (float *) for glVertex3fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	//member variables
	float x;
	float y;
	float z;
};
}
#endif	//VECTOR3D_H
