#include "linuxwindow.h"
#include "../graphics/drawing3d.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glxext.h>
#include <iostream>
#include <string>

namespace Small
{
// FIXME: Siempre trabajamos en 16 bits
bool Window::Open(char *Title, int x, int y, int Width, int Height, int Depth, bool FullScreen)
{
	XSetWindowAttributes attr;
	XVisualInfo *vi;
	Colormap cmap;
	int dpyWidth, dpyHeight;
	int i;
	XF86VidModeModeInfo **modes;
	int modeNum;
	int bestMode;
	Atom wmDelete;
	::Window winDummy;
	unsigned int borderDummy;

	// Atributos para el "single buffer"
	int attrListSgl[]={GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};
	// Atributos para "double buffer"   
	int attrListDbl[]={GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};

	this->fs = FullScreen;
	// Mejor modo el actual
	bestMode=0;  
	// Conectar al servidor
	this->dpy = XOpenDisplay(0);
	this->screen = DefaultScreen(this->dpy);
	XF86VidModeGetAllModeLines(this->dpy, this->screen, &modeNum, &modes);
	// Guardamos la resoluci para luego restablecerla
	this->deskMode = *modes[0];
	// Buscamos un modo con la resolucion adecuada
	for (i=0; i<modeNum; i++)
	{
		if((modes[i]->hdisplay==Width) && (modes[i]->vdisplay==Height))
		{
			bestMode = i;
		}
	}
	// Escoger la visual
	vi = glXChooseVisual(this->dpy, this->screen, attrListDbl);
	
	// No hay doble buffer
	if (vi==NULL)
		vi= glXChooseVisual(this->dpy, this->screen, attrListSgl);
	
	// Crear un contexto glx
	this->ctx = glXCreateContext(this->dpy, vi, 0, GL_TRUE);
	cmap = XCreateColormap(this->dpy, RootWindow(this->dpy, vi->screen), vi->visual, AllocNone);
	attr.colormap = cmap;
	attr.border_pixel= 0;

	if (this->fs)
	{
		XF86VidModeSwitchToMode(this->dpy, this->screen, modes[bestMode]);
		XF86VidModeSetViewPort(this->dpy, this->screen, 0 ,0);
		dpyWidth = modes[bestMode]->hdisplay;
		dpyHeight = modes[bestMode]->vdisplay;
		XFree(modes);
		// Creamos la ventana
		attr.override_redirect=True;
		// La mascara de eventos a recibir. Todavia faltan unos cuantos (movimiento del raton, etc)
		attr.event_mask= ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | StructureNotifyMask | FocusChangeMask | PointerMotionMask;
		this->win = XCreateWindow(this->dpy, RootWindow(this->dpy, vi->screen), 
			0, 0, dpyWidth, dpyHeight, 0, vi->depth, InputOutput, vi->visual, 
			CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &attr);
		XWarpPointer(this->dpy, None, this->win, 0,0,0,0,0,0);
		XMapRaised(this->dpy, this->win);
		XGrabKeyboard(this->dpy, this->win, True, GrabModeAsync, GrabModeAsync, CurrentTime);
		XGrabPointer(this->dpy, this->win, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, 
			this->win, None, CurrentTime);
	}
	else
	{
		attr.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | StructureNotifyMask | FocusChangeMask | PointerMotionMask;
		this->win = XCreateWindow(this->dpy, RootWindow(this->dpy, vi->screen), 0, 0,
			Width, Height, 0, vi->depth, InputOutput, vi->visual, 
			CWBorderPixel | CWColormap | CWEventMask, &attr);
		wmDelete = XInternAtom(this->dpy, "WM_DELETE_WINDOW", True);
		XSetWMProtocols(this->dpy, this->win, &wmDelete, 1);
		XSetStandardProperties(this->dpy, this->win, Title, Title, None, NULL, 0, NULL);
		XMapRaised(this->dpy, this->win);
		// Colocamos el ratón en la ventana
		XGrabPointer(this->dpy, this->win, true, 0, GrabModeAsync, GrabModeAsync, this->win, None, CurrentTime);
	}
	
	// Situamos el ratón en el centro de la ventana
	XWarpPointer(this->dpy, None, this->win, 0, 0, 0, 0, this->width/2, this->height/2);
	// Ocultamos el puntero del ratón
	
	glXMakeCurrent(this->dpy, this->win, this->ctx);
	XGetGeometry(this->dpy, this->win, &winDummy, &this->x, &this->y, &this->width, &this->height, &borderDummy, &this->depth);

	Drawing3D::Instance().Init();//InitGL();

	return true;
};



void Window::Close(void)
{
	if (this->ctx)
	{
		if (!glXMakeCurrent(this->dpy, None, NULL))
			std::cout << "Could not release drawing context." << std::endl;
		glXDestroyContext(this->dpy, this->ctx);
		this->ctx = NULL;
	}
	if (this->fs)
	{
		XF86VidModeSwitchToMode(this->dpy, this->screen, &this->deskMode);
		XF86VidModeSetViewPort(this->dpy, this->screen, 0, 0);
	}
	else
		XUngrabPointer(this->dpy, CurrentTime);
	
	XKeyboardControl _kb;

	_kb.auto_repeat_mode = this->deskKeyboardState.global_auto_repeat;
	XChangeKeyboardControl(this->dpy, KBAutoRepeatMode, &_kb);
	XCloseDisplay(this->dpy);
};

void Window::OnResize(int NewWidth, int NewHeight)
{
	this->width=NewWidth;
	this->height=NewHeight;

	// Y actualizamos openGL
	unsigned int h=this->height;
	if (h==0)
		h=1;

	//FIXME: El código openGL no debería estar aquí
	glViewport(0,0, this->width, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)this->width/(GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

int isExtensionSupported(const char *extension)
 {
   const GLubyte *extensions = NULL;
   const GLubyte *start;
   GLubyte *where, *terminator;
  /* Extension names should not have spaces. */
   where = (GLubyte *) strchr(extension, ' ');
   if (where || *extension == '\0')
     return 0;
   extensions = glGetString(GL_EXTENSIONS);
   /* It takes a bit of care to be fool-proof about parsing the
      OpenGL extensions string. Don't be fooled by sub-strings,
      etc. */
   start = extensions;
   for (;;) {
     where = (GLubyte *) strstr((const char *) start, extension);
     if (!where)
       break;
     terminator = where + strlen(extension);
     if (where == start || *(where - 1) == ' ')
       if (*terminator == ' ' || *terminator == '\0')
         return 1;
     start = terminator;
   }
   return 0;
 }

/*
	if (!isExtensionSupported("GL_ARB_multitexture"))
		std::cout << "No soportada multitextura" << std::endl;
*/
	
void Window::Refresh(void)
{
	glXSwapBuffers(this->dpy, this->win);
};

void Window::Update(void)
{
	XEvent event;

	// Obtenemos y procesamos los eventos de ventana
	long mascaraWindow = EnterWindowMask | LeaveWindowMask | FocusChangeMask | ResizeRedirectMask ; 
	while (XCheckMaskEvent(Small::Window::Instance().dpy,  mascaraWindow, &event))
	{
		switch(event.type)
		{
			case FocusIn:
				OnFocusIn();
				break;
			case FocusOut:
				OnFocusOut();
				break;
			case ConfigureNotify:
				OnResize(event.xconfigure.width, event.xconfigure.height);
				break;
		};
	};
};

void Window::OnFocusOut(void)
{
	//FIXME: Hay que liberar el ratón
	XKeyboardControl _kb;
	_kb.auto_repeat_mode = this->deskKeyboardState.global_auto_repeat;
	XChangeKeyboardControl(this->dpy, KBAutoRepeatMode, &_kb);
};

void Window::OnFocusIn(void)
{
	//FIXME: Hay que volver a obtener el ratón
	// Guardamos el estado del teclado para poder restaurarlo
	XGetKeyboardControl(this->dpy, &deskKeyboardState);
	// Y quitamos el auto_repeat
	XAutoRepeatOff(this->dpy);
};



}


