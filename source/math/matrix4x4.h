//////////////////////////////////////////////////////////////////////////////////////////
//	Matrix4x4.h
//	Class declaration for a 4x4 matrix
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Updated:	19th August 2002	-	Corrected 2nd SetPerspective for n!=1.0f
//				26th September 2002	-	Added nudge to prevent artifacts with infinite far plane
//									-	Improved speed
//				7th November 2002	-	Added Affine Inverse functions
//									-	Changed constructors
//									-	Added special cases for row3 = (0, 0, 0, 1)
//				17th December 2002	-	Converted from radians to degrees for consistency
//										with OpenGL. Should have been done a long time ago...
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

namespace Small 
{
class Matrix4x4
{
public:
	Matrix4x4()
	{	LoadIdentity();	}
	Matrix4x4(	float e0, float e1, float e2, float e3,
				float e4, float e5, float e6, float e7,
				float e8, float e9, float e10, float e11,
				float e12, float e13, float e14, float e15);
	Matrix4x4(const float * rhs);
	Matrix4x4(const Matrix4x4 & rhs);
	~Matrix4x4() {}	//empty

	void SetEntry(int position, float value);
	float GetEntry(int position) const;
	Vector4d GetRow(int position) const;
	Vector4d GetColumn(int position) const;
	
	void LoadIdentity(void);
	void LoadZero(void);
	
	//binary operators
	Matrix4x4 operator+(const Matrix4x4 & rhs) const;
	Matrix4x4 operator-(const Matrix4x4 & rhs) const;
	Matrix4x4 operator*(const Matrix4x4 & rhs) const;
	Matrix4x4 operator*(const float rhs) const;
	Matrix4x4 operator/(const float rhs) const;
	friend Matrix4x4 operator*(float scaleFactor, const Matrix4x4 & rhs);

	bool operator==(const Matrix4x4 & rhs) const;
	bool operator!=(const Matrix4x4 & rhs) const;

	//self-add etc
	void operator+=(const Matrix4x4 & rhs);
	void operator-=(const Matrix4x4 & rhs);
	void operator*=(const Matrix4x4 & rhs);
	void operator*=(const float rhs);
	void operator/=(const float rhs);

	//unary operators
	Matrix4x4 operator-(void) const;
	Matrix4x4 operator+(void) const {return (*this);}
	
	//multiply a vector by this matrix
	Vector4d operator*(const Vector4d rhs) const;

	//rotate a 3d vector by rotation part
	void RotateVector3D(Vector3d & rhs) const
	{rhs=GetRotatedVector3D(rhs);}

	void InverseRotateVector3D(Vector3d & rhs) const
	{rhs=GetInverseRotatedVector3D(rhs);}

	Vector3d GetRotatedVector3D(const Vector3d & rhs) const;
	Vector3d GetInverseRotatedVector3D(const Vector3d & rhs) const;

	//translate a 3d vector by translation part
	void TranslateVector3D(Vector3d & rhs) const
	{rhs=GetTranslatedVector3D(rhs);}

	void InverseTranslateVector3D(Vector3d & rhs) const
	{rhs=GetInverseTranslatedVector3D(rhs);}
	
	Vector3d GetTranslatedVector3D(const Vector3d & rhs) const;
	Vector3d GetInverseTranslatedVector3D(const Vector3d & rhs) const;

	//Other methods
	void Invert(void);
	Matrix4x4 GetInverse(void) const;
	void Transpose(void);
	Matrix4x4 GetTranspose(void) const;
	void InvertTranspose(void);
	Matrix4x4 GetInverseTranspose(void) const;

	//Inverse of a rotation/translation only matrix
	void AffineInvert(void);
	Matrix4x4 GetAffineInverse(void) const;
	void AffineInvertTranspose(void);
	Matrix4x4 GetAffineInverseTranspose(void) const;

	//set to perform an operation on space - removes other entries
	void SetTranslation(const Vector3d & translation);
	void SetScale(const Vector3d & scaleFactor);
	void SetUniformScale(const float scaleFactor);
	void SetRotationAxis(const double angle, const Vector3d & axis);
	void SetRotationX(const double angle);
	void SetRotationY(const double angle);
	void SetRotationZ(const double angle);
	void SetRotationEuler(const double angleX, const double angleY, const double angleZ);
	void SetPerspective(float left, float right, float bottom, float top, float n, float f);
	void SetPerspective(float fovy, float aspect, float n, float f);
	void SetOrtho(float left, float right, float bottom, float top, float n, float f);

	//set parts of the matrix
	void SetTranslationPart(const Vector3d & translation);
	void SetRotationPartEuler(const double angleX, const double angleY, const double angleZ);
	void SetRotationPartEuler(const Vector3d & rotations)
	{
		SetRotationPartEuler((double)rotations.x, (double)rotations.y, (double)rotations.z);
	}

	//cast to pointer to a (float *) for glGetFloatv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}
	
	//member variables
	float entries[16];
};
}
#endif	//Matrix4x4_H
