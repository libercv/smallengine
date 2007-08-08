#ifndef FONT_H
#define FONT_H

#include <windows.h>
#include <stdio.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include "ifont.h"

namespace Small
{
	class Font : public IFont
	{
	private:
		GLuint base;

	public:
		Font(void);
		~Font(void);

		void Print(const char *fmt, ...);
	};
} // namespace Small

#endif
