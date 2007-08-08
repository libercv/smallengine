//////////////////////////////////////////////////////////////////////////////////////////
//	Color.h
//	Class declaration for an RGBA color
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	7th November 2002	-	Some speed improvements
//									-	Removed clamping after adds etc. Do it yourself!
//										To enable use with floating point color buffers
//									-	Corrected lerp (reversed f and 1-f)
//				13th December 2002	-	Added default parameter to alpha of Set()
//									-	Added red, green, blue constant Colors
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef COLOR_H
#define COLOR_H
namespace Small 
{
class Color
{
public:
	//constructors
	Color()
	{	r=g=b=a=0.0f;	}

	Color(float newR, float newG, float newB, float newA=0.0f)
	{	r=newR;	g=newG;	b=newB;	a=newA;	}

	Color(const float * rhs)
	{	r=*rhs;	g=*(rhs+1);	b=*(rhs+2); a=*(rhs+3);	}

	Color(const Color & rhs)
	{	r=rhs.r;	g=rhs.g;	b=rhs.b;	a=rhs.a;}

	~Color() {}	//empty

	void Set(float newR, float newG, float newB, float newA=0.0f)
	{	r=newR;	g=newG;	b=newB;	a=newA;	}
	
	//accessors kept for compatability
	void SetR(float newR) {r = newR;}
	void SetG(float newG) {g = newG;}
	void SetB(float newB) {b = newB;}
	void SetA(float newA) {a = newA;}
	
	float GetR() const {return r;}	//public accessor functions
	float GetG() const {return g;}	//inline, const
	float GetB() const {return b;}
	float GetA() const {return a;}

	void ClampTo01(void);			//clamp all components to [0,1]

	void SetBlack(void) {r=g=b=a=1.0f;}
	void SetWhite(void) {r=g=b=a=0.0f;}
	void SetGrey(float shade) {r=g=b=a=shade;}

	//linear interpolate
	Color lerp(const Color & c2, float factor)
	{	return (*this)*(1.0f-factor) + c2*factor;	}

	//binary operators
	Color operator+(const Color & rhs) const
	{	return Color(r+rhs.r, g+rhs.g, b+rhs.b, a+rhs.a);	}

	Color operator-(const Color & rhs) const
	{	return Color(r-rhs.r, g-rhs.g, b-rhs.b, a-rhs.a);	}

	Color operator*(const Color & rhs) const
	{	return Color(r*rhs.r, g*rhs.g, b*rhs.b, a*rhs.a);	}

	Color operator/(const Color & rhs) const
	{	return Color(r/rhs.r, g/rhs.g, b/rhs.b, a/rhs.a);	}

	Color operator*(const float rhs) const
	{	return Color(r*rhs, g*rhs, b*rhs, a*rhs);	}

	Color operator/(const float rhs) const
	{	return Color(r/rhs, g/rhs, b/rhs, a/rhs);	}

	//multiply by a float, eg 3*c
	friend Color operator*(float scaleFactor, const Color & rhs);

	bool operator==(const Color & rhs) const;
	bool operator!=(const Color & rhs) const
	{	return !((*this)==rhs);	}

	//self-add etc
	Color operator+=(const Color & rhs)
	{	(*this)=(*this)+rhs;	return (*this);	}

	Color operator-=(const Color & rhs)
	{	(*this)=(*this)-rhs;	return (*this);	}

	Color operator*=(const Color & rhs)
	{	(*this)=(*this)*rhs;	return (*this);	}

	Color operator/=(const Color & rhs)
	{	(*this)=(*this)/rhs;	return (*this);	}

	Color operator*=(const float rhs)
	{	(*this)=(*this)*rhs;	return (*this);	}

	Color operator/=(const float rhs)
	{	(*this)=(*this)/rhs;	return (*this);	}

	//unary operators
	Color operator-(void) const {return Color(-r,-g, -b, -a);}
	Color operator+(void) const {return (*this);}

	//cast to pointer to float for glColor4fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	//member variables
	float r;
	float g;
	float b;
	float a;
};

const Color white(1.0f, 1.0f, 1.0f, 1.0f);
const Color black(0.0f, 0.0f, 0.0f, 0.0f);

const Color red(1.0f, 0.0f, 0.0f, 1.0f);
const Color green(0.0f, 1.0f, 0.0f, 1.0f);
const Color blue(0.0f, 0.0f, 1.0f, 1.0f);
}
#endif	//COLOR_H
