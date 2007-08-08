//////////////////////////////////////////////////////////////////////////////////////////
//	Plane.h
//	Class declaration for a plane in 3d space
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	6th August 2002		-	Added "Normalize"
//				7th November 2002	-	Altered constructor layout
//									-	Corrected "lerp"
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef PLANE_H
#define PLANE_H

namespace Small
{

class Plane
{
public:
	Plane()	:	normal(Vector3d(0.0f, 0.0f, 0.0f)), intercept(0.0f)
	{}
	Plane(Vector3d newNormal, float newIntercept)	: normal(newNormal), intercept(newIntercept)
	{}
	Plane(const Plane & rhs)
	{	normal=rhs.normal;	intercept=rhs.intercept;	}

	~Plane() {}
	
	void SetNormal(const Vector3d & rhs) { normal=rhs; }
	void SetIntercept(float newIntercept) { intercept=newIntercept; }
	void SetFromPoints(const Vector3d & p0, const Vector3d & p1, const Vector3d & p2);

	void CalculateIntercept(const Vector3d & pointOnPlane) { intercept=-normal.DotProduct(pointOnPlane); }
	
	void Normalize(void);

	Vector3d GetNormal() { return normal; }
	float GetIntercept() { return intercept; }
	
	//find point of intersection of 3 planes
	bool Intersect3(const Plane & p2, const Plane & p3, Vector3d & result);

	float GetDistance(const Vector3d & point) const;
	int ClassifyPoint(const Vector3d & point) const;
	
	Plane lerp(const Plane & p2, float factor);

	//operators
	bool operator==(const Plane & rhs) const;
	bool operator!=(const Plane & rhs) const
	{		return!((*this)==rhs);	}

	//unary operators
	Plane operator-(void) const {return Plane(-normal, -intercept);}
	Plane operator+(void) const {return (*this);}

	//member variables
	Vector3d normal;	//X.N+intercept=0
	float intercept;
};

//constants for ClassifyPoint()
const int POINT_ON_PLANE=0;
const int POINT_IN_FRONT_OF_PLANE=1;
const int POINT_BEHIND_PLANE=2;

}
#endif //PLANE_H
