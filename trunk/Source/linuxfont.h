#ifndef FONT_H
#define FONT_H

#include <stdio.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/extensions/xf86vmode.h>

namespace Small
{

#include "ifont.h"


class Font : public IFont
{
private:
	GLuint base;

public:
	Font();
	~Font(void);

	void Print(const char *fmt, ...);
};
}
#endif
