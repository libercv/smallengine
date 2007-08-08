//////////////////////////////////////////////////////////////////////////////////////////
//	Maths.h
//	Include maths headers
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	17th December 2002	-	Removed QUATERNION
//////////////////////////////////////////////////////////////////////////////////////////	
#ifndef MATH_H
#define MATH_H

#include <math.h>

//VC++ math.h (and others) do not define M_PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//An epsilon value for comparisons
#ifndef EPSILON
#define EPSILON 0.01f
#endif

#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "matrix4x4.h"
#include "plane.h"

#include "color.h"

#endif // MATH_H
