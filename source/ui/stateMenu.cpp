
#include "stateMenu.h"

namespace Small
{

StateMenu::StateMenu(void)
{
	texture = CTextureManager::GetInstance()->LoadTexture("resources/textures/small.bmp");
	
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
	float w,h;
	short a;

	// Tamaño de la Ventana
	WinW = Window::Instance().GetWidth();
	WinH = Window::Instance().GetHeight();

	// Tamaño del titulo
	w = 256;
	h = 64;

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	StateGame::Instance().Render();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// PENDIENTE: coger el ancho y alto de la ventana
	glViewport(0,0,(GLsizei)WinW,(GLsizei)WinH);
	glOrtho(0,WinW, 0,WinH, -10.0, 10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);	
	glDisable(GL_LIGHTING);	

	// Oscurecemos la escena
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

	///////////////////

	glColor3f(1.0f,0.0f,0.0f);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();
		glTranslatef((WinW-w)/2.0f, (WinH*0.95f)-h, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f); glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(1.0f,1.0f); glVertex3f(w,0.0f,0.0f);
			glTexCoord2f(1.0f,0.0f); glVertex3f(w,h,0.0f);
			glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f,h,0.0f);
		glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);

	// PENDIENTE: quitar el 5 a pi�n
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
	glColor3f(0.0f,0.0f,1.0f);
	glRasterPos2f(5,90);
	System::Instance().oFont->Print("Vendor:%s",glGetString(GL_VENDOR));
	glRasterPos2f(5,60);
	System::Instance().oFont->Print("Renderer:%s",glGetString(GL_RENDERER));
	glRasterPos2f(5,30);
	System::Instance().oFont->Print("Version:%s",glGetString(GL_VERSION));
	*/

	//glEnable(GL_LIGHTING);	
	glEnable(GL_DEPTH_TEST);
}

void StateMenu::Update(unsigned long ElapsedTime)
{
	if( Input::Instance().IsKeyPressed(KeyEscape) )
	{
		// PENDIENTE: cuidad� !!! State tiende a ser de Game y no de Engine.
		Engine::Instance().CurrentState = State::StateId::Game;
	}
	if( Input::Instance().IsKeyPressed(KeyReturn) )
	{
		if( SelectedItemIndex==5 )
			Engine::Instance().CurrentState = State::StateId::Done;
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
}

} //namespace Small
