#ifndef IFONT_H
#define IFONT_H

class IFont
{
public:
	virtual void Print(const char *fmt, ...) = 0;
};

#endif
