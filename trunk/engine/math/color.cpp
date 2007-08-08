//////////////////////////////////////////////////////////////////////////////////////////
//	COLOR.cpp
//	function definitions for an RGBA color class
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	7th November 2002	-	Some speed improvements
//									-	Removed clamping after adds etc. Do it yourself!
//										To enable use with floating point color buffers
//									-	Corrected lerp (reversed f and 1-f)
//////////////////////////////////////////////////////////////////////////////////////////	

#include "color.h"
namespace Small
{

void Color::ClampTo01()
{
	if(r>1.0f)
		r=1.0f;
	if(r<0.0f)
		r=0.0f;

	if(g>1.0f)
		g=1.0f;
	if(g<0.0f)
		g=0.0f;

	if(b>1.0f)
		b=1.0f;
	if(b<0.0f)
		b=0.0f;

	if(a>1.0f)
		a=1.0f;
	if(a<0.0f)
		a=0.0f;
}

Color operator*(float scaleFactor, const Color & rhs)
{
	return rhs*scaleFactor;
}

bool Color::operator ==(const Color & rhs) const
{
	if(r != rhs.r)
		return false;
	if(g != rhs.g)
		return false;
	if(b != rhs.b)
		return false;
	if(a != rhs.a)
		return false;

	return true;
}
}
