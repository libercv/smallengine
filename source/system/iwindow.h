#ifndef IWINDOW_H
#define IWINDOW_H

class IWindow
{
public:
	virtual bool Open(char *Title, int X, int Y, int Width, int Height, int ColorDepth, bool FullScreen) = 0;
	virtual void Close(void) = 0;
	virtual void Refresh(void) = 0;

	virtual int GetWidth(void) = 0;
	virtual int GetHeight(void) = 0;
};

#endif // IWINDOW_H
