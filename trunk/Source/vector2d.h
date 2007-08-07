//////////////////////////////////////////////////////////////////////////////////////////
//	Vector2d.h
//	Class declaration for a 2d vector
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	6th November 2002
//	Modified:	7th January 2003	-	Added QuadraticInterpolate
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef VECTOR2D_H
#define VECTOR2D_H


#include <math.h>
namespace Small
{
class Vector2d
{
public:
	//constructors
	Vector2d(void)	:	x(0.0f), y(0.0f)
	{}

	Vector2d(float newX, float newY):	x(newX), y(newY)
	{}

	Vector2d(const float * rhs)		:	x(*rhs), y((*rhs)+1)
	{}

	Vector2d(const Vector2d & rhs)	:	x(rhs.x), y(rhs.y)
	{}

	~Vector2d() {}	//empty

	void Set(float newX, float newY)
	{	x=newX;	y=newY;	}
	
	//Accessors kept for compatibility
	void SetX(float newX) {x = newX;}
	void SetY(float newY) {y = newY;}

	float GetX() const {return x;}	//public accessor functions
	float GetY() const {return y;}	//inline, const

	void LoadZero(void);
	void LoadOne(void);					//fill with (1, 1)
	
	void Normalize();
	Vector2d GetNormalized() const;
	
	float GetLength() const
	{	return (float)sqrt((x*x)+(y*y));	}
	
	float GetSquaredLength() const
	{	return (x*x)+(y*y);	}

	//linear interpolate
	Vector2d lerp(const Vector2d & v2, float factor) const
	{	return (*this)*(1.0f-factor) + v2*factor;	}

	Vector2d QuadraticInterpolate(const Vector2d & v2, const Vector2d & v3, float factor) const
	{	return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;}

	//overloaded operators
	//binary operators
	Vector2d operator+(const Vector2d & rhs) const
	{	return Vector2d(x + rhs.x, y + rhs.y);	}

	Vector2d operator-(const Vector2d & rhs) const
	{	return Vector2d(x - rhs.x, y - rhs.y);	}

	Vector2d operator*(const float rhs) const
	{	return Vector2d(x*rhs, y*rhs);	}
	
	Vector2d operator/(const float rhs) const
	{	return (rhs==0) ? Vector2d(0.0f, 0.0f) : Vector2d(x / rhs, y / rhs);	}

	//multiply by a float, eg 3*v
	friend Vector2d operator*(float scaleFactor, const Vector2d & rhs);

	bool operator==(const Vector2d & rhs) const;
	bool operator!=(const Vector2d & rhs) const
	{	return !((*this)==rhs);	}

	//self-add etc
	void operator+=(const Vector2d & rhs)
	{	x+=rhs.x;	y+=rhs.y;}

	void operator-=(const Vector2d & rhs)
	{	x-=rhs.x;	y-=rhs.y;}

	void operator*=(const float rhs)
	{	x*=rhs;	y*=rhs;	}

	void operator/=(const float rhs)
	{	if(rhs==0.0f)
			return;
		else
		{	x/=rhs; y/=rhs;	}
	}


	//unary operators
	Vector2d operator-(void) const {return Vector2d(-x, -y);}
	Vector2d operator+(void) const {return *this;}

	//cast to pointer to a (float *) for glVertex3fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	//member variables
	float x;
	float y;
};
}
#endif	//VECTOR2D_H
