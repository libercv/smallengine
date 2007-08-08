#include "linuxfont.h"
#include "../system/window.h"
#include <stdarg.h>
#include <string> 
#include <iostream>

namespace Small
{
using namespace std;

Font::Font()
{
    XFontStruct *font;

    base = glGenLists(96);
    font = XLoadQueryFont(Small::Window::Instance().dpy, "-adobe-helvetica-bold-r-normal-*-24-240-75-75-p-*-iso8859-1");
    if( font == NULL )
    {
        font = XLoadQueryFont(Small::Window::Instance().dpy, "fixed");
        if (font == NULL)
        {
            printf("Problems loading fonts :-(\n");
            exit(1);
        }
    }
    glXUseXFont(font->fid, 32, 96, base);
    XFreeFont(Small::Window::Instance().dpy, font);
}

Font::~Font(void)
{
    glDeleteLists(base, 96);
}

void Font::Print(const char *fmt, ...)
{
	char text[256];
	va_list ap;

	if (fmt == NULL)
		return;

	va_start(ap, fmt);
		vsprintf(text, fmt, ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
		glListBase(base - 32);
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}
};
