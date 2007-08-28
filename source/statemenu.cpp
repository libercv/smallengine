
#include "statemenu.h"

namespace Small
{

StateMenu::StateMenu(void)
{
	texture = CTextureManager::GetInstance()->LoadTexture("resources/textures/Small.tga");
	mask = CTextureManager::GetInstance()->LoadTexture("resources/textures/SmallMask.tga");
	
	SelectedItemIndex = 0;

	Items.push_back("Nueva partida");
	Items.push_back("Continuar partida");
	Items.push_back("Opciones de video");
	Items.push_back("Opciones de audio");
	Items.push_back("Opciones de juego");
	Items.push_back("Salir del juego");
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

	float textW=256, textH=128;
	float x1=(WinW/2)-(textW/2), y1=80-(textH/2);
	float x2=(WinW/2)+(textW/2), y2=80+(textH/2);

	//glDisable(GL_LIGHTING);

	Drawing3D::Instance().OrthoMode(0,0,(GLsizei)WinW,(GLsizei)WinH);
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

	glEnable(GL_BLEND);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Pintamos la máscara del logo
	glBindTexture(GL_TEXTURE_2D, mask);
	glBlendFunc(GL_ONE,GL_ONE);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(x1, y1);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(x1, y2);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(x2, y2);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(x2, y1);
	glEnd();	

	// Pintamos el logo
	glBindTexture(GL_TEXTURE_2D, texture);
	glBlendFunc(GL_DST_COLOR,GL_ZERO);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(x1, y1);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(x1, y2);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(x2, y2);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(x2, y1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);
	
	// Pintamos el menú
	for( a=0; a<=5; a++ )
	{
		if( a == SelectedItemIndex )
			glColor3f(0.5f,0.5f,1.0f);
		else
			glColor3f(1.0f,1.0f,0.0f);

		glRasterPos2f((float)(WinW/2)-100, (float)(150+(a*30)));
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

	//glEnable(GL_LIGHTING);	
	glEnable(GL_DEPTH_TEST);

	Drawing3D::Instance().PerspectiveMode(Window::Instance().GetWidth(), Window::Instance().GetHeight());
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

} //namespace Small

