
#include "log.h"

namespace Small
{
Log::Log()
{
	LogFile.open("smalllog.txt");
}

Log::~Log()
{
	LogFile.close();
}

void Log::Write(const char *fmt, ...)
{
	char text[256];
	va_list ap;

	if( fmt == NULL )
		return;

	va_start(ap, fmt);
		vsprintf(text, fmt, ap);
	va_end(ap);

	LogFile << text << std::endl;
}
} // namespace Small
