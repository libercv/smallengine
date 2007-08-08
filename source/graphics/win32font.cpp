
#include "win32font.h"

#include "../system/win32window.h"

namespace Small
{

Font::Font(void)
{
	HFONT font;
	HFONT oldfont;

	base = glGenLists(96);

	font = CreateFont(	-24,
						0,
						0,
						0,
						FW_BOLD,
						FALSE,
						FALSE,
						FALSE,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						"Courier New");

	oldfont = (HFONT)SelectObject(Window::Instance().GetContext(), font);
	wglUseFontBitmaps(Window::Instance().GetContext(), 32, 96, base);
	SelectObject(Window::Instance().GetContext(), oldfont);
	DeleteObject(font);
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

}