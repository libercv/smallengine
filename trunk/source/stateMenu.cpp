
#include "stateMenu.h"

namespace Small
{

StateMenu::StateMenu(void)
{
	texture = CTextureManager::GetInstance()->LoadTexture("resources/textures/SmallMask.tga");
	mask = CTextureManager::GetInstance()->LoadTexture("resources/textures/Small.tga");
	
	SelectedItemIndex = 0;

	Items.push_back("Start New Game");
	Items.push_back("Continue Game");
	Items.push_back("Video Options");
	Items.push_back("Audio Options");
	Items.push_back("Game Settings");
	Items.push_back("Quit Game");
}

void StateMenu::Render(void)
{
	int WinW, WinH;
	short a;

	// Tamaño de la Ventana
	WinW = Window::Instance().GetWidth();
	WinH = Window::Instance().GetHeight();

	//glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// PENDIENTE: no no no no no... los estados no se ven entre si y mucho menos se llaman.
	StateGame::Instance().Render();

	float textW=157, textH=76;
	float x1=(WinW/2)-(textW/2), y1=390-(textH/2);
	float x2=(WinW/2)+(textW/2), y2=390+(textH/2);

	glDisable(GL_LIGHTING);

	OrthoMode(0,0,(GLsizei)WinW,(GLsizei)WinH);
	glDisable(GL_DEPTH_TEST);

	// Oscurecemos la escena
	/*
	glColor4f(0.5f,0.5f,0.5f,0.5f);
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
			glVertex2f(0.0f,(float)WinH);
			glVertex2f(0.0f,0.0f);
			glVertex2f((float)WinW,0.0f);
			glVertex2f((float)WinW,(float)WinH);
		glEnd();
	glDisable(GL_BLEND);
	*/

	// Pintamos la máscara del logo
	glBlendFunc(GL_DST_COLOR,GL_ZERO);
	glEnable(GL_BLEND);			

	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, mask);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(x1, y1);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(x1, y2);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(x2, y2);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(x2, y1);
	glEnd();	

	// Pintamos el logo
	glBlendFunc(GL_ONE,GL_ONE);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(x1, y1);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(x1, y2);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(x2, y2);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(x2, y1);
	glEnd();

	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Pintamos el menú
	for( a=0; a<=5; a++ )
	{
		if( a == SelectedItemIndex )
			glColor3f(0.5f,0.5f,1.0f);
		else
			glColor3f(1.0f,1.0f,0.0f);

		glRasterPos2f((float)220, (float)(330-(a*30)));
		Drawing3D::Instance().BigFont->Print(Items[a].c_str());
	}

	/*
	// Pintamos información de la tarjeta gráfica
	glColor3f(0.5f, 0.5f, 1.0f);
	glRasterPos2f(5.0f, 90.0f);
	Drawing3D::Instance().BigFont->Print("Vendor:%s",glGetString(GL_VENDOR));
	glRasterPos2f(5.0f, 60.0f);
	Drawing3D::Instance().BigFont->Print("Renderer:%s",glGetString(GL_RENDERER));
	glRasterPos2f(5.0f, 30.0f);
	Drawing3D::Instance().BigFont->Print("Version:%s",glGetString(GL_VERSION));
	*/

	glEnable(GL_LIGHTING);	
	glEnable(GL_DEPTH_TEST);

	PerspectiveMode();
}

EngineStateEnum StateMenu::Update(float ElapsedTime)
{
	EngineStateEnum NextState = Menu;

	if( Input::Instance().IsKeyPressed(KeyEscape) )
	{
		// PENDIENTE: StateMenu no debe ver a Engine. Mejor que devuelva el siguiente estado.
		//Engine::Instance().CurrentState = State::StateId::Game;
		NextState = Game;
	}
	if( Input::Instance().IsKeyPressed(KeyReturn) )
	{
		if( SelectedItemIndex==5 )
			NextState = Done;
			//Engine::Instance().CurrentState = State::StateId::Done;
	}
	else if( Input::Instance().IsKeyPressed(KeyDown) )
	{
		++SelectedItemIndex %= 6; // PENDIENTE: quitar el 6 a pi�n
	}
	else if( Input::Instance().IsKeyPressed(KeyUp) )
	{
		if( SelectedItemIndex>0 )
			SelectedItemIndex--;
		else
			SelectedItemIndex=5; // PENDIENTE: quitar el 5 a pi�n

	}

	return NextState;
}

void StateMenu::OrthoMode(int left, int top, int right, int bottom)
{
	// This function takes in rectangle coordinates for our 2D view port.
	// What happens below is, we need to change our projection matrix.  To do this,
	// we call glMatrixMode(GL_PROJECTION) to tell OpenGL the current mode we want.
	// Then we push on a new matrix so we can just call glPopMatrix() to return us
	// to our previous projection matrix, but first we will render in ortho mode.
	//  Next, we load a new identity matrix so that everything is initialize before
	// we go into ortho mode.  One we switch to ortho by calling glOrth(), we then
	// want to set our matrix mode to GL_MODELVIEW, which puts us back and ready to
	// render our world using the model matrix.  We also initialize this new model view
	// matrix for our 2D rendering before drawing anything.

	// Switch to our projection matrix so that we can change it to ortho mode, not perspective.
	glMatrixMode(GL_PROJECTION);						

	// Push on a new matrix so that we can just pop it off to go back to perspective mode
	glPushMatrix();									
	
	// Reset the current matrix to our identify matrix
	glLoadIdentity();								

	//Pass in our 2D ortho screen coordinates.like so (left, right, bottom, top).  The last
	// 2 parameters are the near and far planes.
	glOrtho( left, right, top, bottom, 0, 1 );	
	
	// Switch to model view so that we can render the scope image
	glMatrixMode(GL_MODELVIEW);								

	// Initialize the current model view matrix with the identity matrix
	glLoadIdentity();										
}


///////////////////////////////// PERSPECTIVE MODE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function changes our returns our projection mode from 2D to 3D
/////
///////////////////////////////// PERSPECTIVE MODE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void StateMenu::PerspectiveMode()
{
	// This function doesn't really go to perspective mode, since we aren't
	// using gluPerspective(), but if you look in OrthoMode(), we push on
	// a matrix once we change to our projection matrix.  All we need to do is
	// pop that matrix off of our stack and it will return to our original perspective
	// matrix.  So, before we pop the current matrix, we need to tell OpenGL which
	// matrix we want to use by changing our current matrix mode to perspective.
	// Then we can go back to our model view matrix and render normally.

	// Enter into our projection matrix mode
	glMatrixMode( GL_PROJECTION );							

	// Pop off the last matrix pushed on when in projection mode (Get rid of ortho mode)
	glPopMatrix();											

	// Go back to our model view matrix like normal
	glMatrixMode( GL_MODELVIEW );							

	// We should be in the normal 3D perspective mode now
}



} //namespace Small

