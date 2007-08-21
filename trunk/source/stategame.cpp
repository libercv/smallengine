
#include "stategame.h"

namespace Small
{

StateGame::StateGame(void)
{
#ifdef _WIN32
	// RedirectIOToConsole();
#endif
	// PENDIENTE: cuanto antes saquemos la carga del escenario a un fichero mejor.

	iCamera = 0;

	Bsp.frustum = &Frustum;
	Bsp.LoadBSP("resources/maps/Tutorial.bsp"); // PENDIENTE: controlar que se carga bien el BSP. 

	/*
	Object *NewObject = new Object();
	NewObject->Model = new CMD2Model();
	NewObject->Model->LoadModel("resources/models/yoshi.md2");
	NewObject->Model->LoadSkin("resources/models/yoshi.bmp");
	NewObject->Model->SetAnim( RUN );
	// NewObject->Model->ScaleModel( 1.0f );
	// NewObject->SetPath( &Path );
	Objects.push_back(*NewObject);
	*/

	Player *NewPlayer = new Player();
	NewPlayer->Model = new CMD2Model();
	NewPlayer->Model->LoadModel("resources/models/yoshi.md2");
	NewPlayer->Model->LoadSkin("resources/models/yoshi.bmp");
	NewPlayer->Model->SetAnim( RUN );
	NewPlayer->Position.Set(416.0f, 0.0f, 0.0f);
	// NewPlayer->Model->ScaleModel( 1.0f );
	// NewPlayer->SetPath( &Path );
	Players.push_back(*NewPlayer);

	Camera *NewCamera = new Camera();
	NewCamera->Position.x = 300;
	NewCamera->Position.y = 100;
	NewCamera->Position.z = 400;
	//NewCamera->SetPath( &Path );
	Cameras.push_back(*NewCamera);

	Light *NewLight = new Light();
	NewLight->Position.Set(320.0f, 64.0f, 0.0f);
	//NewLight->SetPath( &Path );
	Lights.push_back(*NewLight);
}

EngineStateEnum StateGame::Update(float ElapsedTime)
{
	EngineStateEnum NextState = Game;

	/*
	int dx,dy;
	Input::Instance().GetMouseMotion(&dx,&dy);
	Cameras[iCamera].RotateView(dx,dy);
	*/

	mouse = CTextureManager::GetInstance()->LoadTexture("resources/textures/mouse.tga");
	mouseMask = CTextureManager::GetInstance()->LoadTexture("resources/textures/mouseMask.tga");

	// PENDIENTE: la pausa se debe implementar como otro estado más.
	if( Engine::Instance().CurrentState == Pause )
	{
		if( Input::Instance().IsKeyPressed(KeyPause) )
			Engine::Instance().CurrentState = Game;
	}
	else
	{
		// Propagamos el Update a todos los jugadores
		for(vector<Player>::iterator PlayerItor=Players.begin(); PlayerItor!=Players.end(); PlayerItor++)
			(*PlayerItor).Update(ElapsedTime, &Bsp);

		// Propagamos el Update a todos los objetos
		for(vector<Object>::iterator ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ObjectItor++)
			(*ObjectItor).Update();

		// Propagamos el Update a todas las luces
		for(vector<Light>::iterator LightItor=Lights.begin(); LightItor!=Lights.end(); LightItor++)
			(*LightItor).Update();

		// Propagamos el Update a todas las camaras
		for(vector<Camera>::iterator CameraItor=Cameras.begin(); CameraItor!=Cameras.end(); CameraItor++)
			(*CameraItor).Update();

		if( Input::Instance().IsKeyPressed(KeyEscape) )
		{
			NextState = Menu;
			// Engine::Instance().CurrentState = State::StateId::Menu;	// PENDIENTE: desde aquí no debemos cambiar el state de Game. Lo devolveremos como retorno.
		}
		else if( Input::Instance().IsKeyPressed(KeyPause) )
		{
			NextState = Pause;
			//Engine::Instance().CurrentState = State::StateId::Pause; // PENDIENTE: desde aquí no debemos cambiar el state de Game. Lo devolveremos como retorno.
		}
		else if( Input::Instance().IsKeyPressed(KeySpace) )
			iCamera = (++iCamera) % Cameras.size();
		else if( Input::Instance().IsKeyPressed(KeyReturn) )
		{
			Lights[0].On = !Lights[0].On;
		}




		// *** PRUEBAS: movemos al bicho ***************************************
		/*
		float BichoSpeed = 130.0f; // unidades/segundo // PENDIENTE: usar la velocidad de la entidad.
		Players[0].Position.x += -(BichoSpeed*ElapsedTime);
		if( Players[0].Position.x < 0.0f ) 
			Players[0].Position.x = 800.0f;
		*/
		// ********************************************************************


		// *** PRUEBAS: movemos la cámara *************************************
		// PENDIENTE: Esto no se debe hacer aquí. Para actualizar la cámara con las entradas de
		// usuario habrá que llamar al update pasándole éstas o la cámara debe ser capaz en el
		// update de obtener las entradas de usuario y usarlas.
		// PENDIENTE: distintos tipos de cámara: unas admiten entradas de usuario. Otras siguen un path.
		// Otras están fijas. ¿Cómo se come eso?

		// PENDIENTE: usar la velocidad de la entidad
		float speed=300.0f; // Unidades/segundo. 
		float fSpeed=0, sSpeed=0;

		/*
		if( Input::Instance().GetKeyState(KeyUp) )
			fSpeed = speed * ElapsedTime;
		else if( Input::Instance().GetKeyState(KeyDown) )
			fSpeed = -1 * speed * ElapsedTime;
		*/

		/*
		if( Input::Instance().GetKeyState(KeyLeft) )
			sSpeed = speed * ElapsedTime;
		else if( Input::Instance().GetKeyState(KeyRight) )
			sSpeed = -1 * speed * ElapsedTime;
		*/

		if( Input::Instance().GetKeyState(KeyHome) )
		{
			Cameras[0].Position.y += speed * ElapsedTime;
			Cameras[0].View.y += speed * ElapsedTime;
		}
		else if( Input::Instance().GetKeyState(KeyEnd) )
		{
			Cameras[0].Position.y -= speed * ElapsedTime;
			Cameras[0].View.y -= speed * ElapsedTime;
		}

		if( fSpeed || sSpeed )
		{
			Vector3d dest = Cameras[0].TryToMove(fSpeed, sSpeed);

			// PENDIENTE: obtener el bounding box de la entidad/objeto
			Vector3d vMax(10, 0, 10);
			Vector3d vMin(-10,-50,-10);

			//Vector3d finalDest= Bsp.TraceSphere(orig, dest, 50);
			Vector3d finalDest = Bsp.TraceBox(Cameras[0].Position, dest, vMin, vMax);

			// PEDNDIENTE: no usar los accesors para miembros atómicos. Mejor pasar un vector3d
			// o usar directamente los miembros
			Cameras[0].Position = finalDest;
		}
		// ********************************************************************

	}

	// Hacemos que la cámara mire al bicho
	Cameras[0].Position.x = Players[0].Position.x;
	Cameras[0].View = Players[0].Position;

	Lights[0].Position.Set(300, 64, 64);

	return NextState;
}

void StateGame::Render(void)
{
	// PENDIENTE: ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ DE AQUI VA CASI TODO FUERA !!!!!!!!!!!!!!!!!!!!!!!!!

	// PENDIENTE: todo lo que se llame gl* Drawing3D. 
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Drawing3D::Instance().PerspectiveMode(45.0f, Window::Instance().GetWidth(), Window::Instance().GetHeight(), 1.0f, 2000.0f);

	Cameras[iCamera].Apply();

	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//Drawing3D::Instance().DrawSkyBox(0,-0.0001,0,400,200,400);
	//Drawing3D::Instance().DrawAxes(64.0f, true);

	//std::cout << Timer::Instance().GetFps() << std::endl;
	//System::Instance().oFont->Print(Timer::Instance().GetFps());
	
	if( !iCamera )
		glColor3f(1.0f, 1.0f, 1.0f);
	else
		glColor3f(0.0f, 1.0f, 0.0f);

	glPushAttrib( GL_POLYGON_BIT );
	{
		glFrontFace( GL_CW );
		Frustum.CalculateFrustum();
		Bsp.RenderLevel(Cameras[iCamera].Position);
	}
	glPopAttrib();
	
/*
	// FIXME: Retirado hasta que este bien probado
	// Pintamos el bicho sólo si cae dentro del frustum
	box_t bBox;
	Objects[0].Model->GetInterpolatedBoundingBox(bBox);
	if (Frustum.BoxInFrustum(bBox[0], bBox[1], bBox[2], bBox[3]-bBox[0], bBox[4]-bBox[1], bBox[5]-bBox[2]))

*/
	// Pintamos los jugadores
	for(vector<Player>::iterator PlayerItor=Players.begin(); PlayerItor!=Players.end(); PlayerItor++)
		(*PlayerItor).Render();

	// Pintamos los Objetos
	for(vector<Object>::iterator ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ObjectItor++)
		(*ObjectItor).Render();

	// Pintamos las cámaras
	for(vector<Camera>::size_type i=0; i<Cameras.size(); i++)
		if( i != iCamera )
			Cameras[i].Render();

	// Pintamos las luces
	for(vector<Light>::iterator LightItor=Lights.begin(); LightItor!=Lights.end(); LightItor++)
		(*LightItor).Render();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	//Cameras[1].Apply();
	Drawing3D::Instance().DrawAxes(32, true);

	Drawing3D::Instance().OrthoMode(0,0, 800,600);

	int x,y;
	Input::Instance().GetMousePosition(&x, &y);

	float mouseX1,mouseY1, mouseX2,mouseY2;

	mouseX1 = (float)x;
	mouseY1 = (float)y;
	mouseX2 = (float)x+32;
	mouseY2 = (float)y+32;

	glEnable(GL_BLEND);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, mouseMask);
	glBlendFunc(GL_ONE,GL_ONE);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(mouseX1, mouseY1);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(mouseX1, mouseY2);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(mouseX2, mouseY2);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(mouseX2, mouseY1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, mouse);
	glBlendFunc(GL_DST_COLOR,GL_ZERO);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(mouseX1, mouseY1);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(mouseX1, mouseY2);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(mouseX2, mouseY2);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(mouseX2, mouseY1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);

	glColor3f(0.5f, 1.0f, 1.0f);

	glRasterPos2f(10.0f, (float)Window::Instance().GetHeight()-100);
	Drawing3D::Instance().BigFont->Print("X=%f  Y=%f Z=%f", Players[0].Position.x, Players[0].Position.y, Players[0].Position.z);

	glRasterPos2f(10.0f, (float)Window::Instance().GetHeight()-75);
	Drawing3D::Instance().BigFont->Print("Time = %f", Timer::Instance().GetElapsedTime());

	glRasterPos2f(10.0f, (float)Window::Instance().GetHeight()-50);
	Drawing3D::Instance().BigFont->Print("Height = %d", Window::Instance().GetHeight());

	glRasterPos2f(10.0f, (float)Window::Instance().GetHeight()-25);
	Drawing3D::Instance().BigFont->Print("X=%f  Y=%f", mouseX1,mouseY1);

	glRasterPos2f(10.0f, (float)Window::Instance().GetHeight());
	Drawing3D::Instance().BigFont->Print("RotationY = %f", Players[0].GetRotationY());

	Drawing3D::Instance().PerspectiveMode(45.0f, Window::Instance().GetWidth(), Window::Instance().GetHeight(), 1.0f, 2000.0f);
	
	/*
	if( iCamera != 0 )
	{
		glPushAttrib( GL_LIGHTING_BIT | GL_DEPTH_BITS );
		{	
			glDisable( GL_LIGHTING_BIT );
			glDisable( GL_DEPTH_TEST );

			int WinW = Window::Instance().GetWidth();
			int WinH = Window::Instance().GetHeight();

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glViewport(0,0,(GLsizei)WinW,(GLsizei)WinH);
			glOrtho(0,WinW, WinH,0, -10.0, 10.0);
		
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
			for( short a=0; a<WinH; a+=2 )
			{
				glBegin( GL_LINES );
					glVertex2d(0,a);
					glVertex2d(WinW,a);
				glEnd();
			}
			glDisable( GL_BLEND );
		}
		glPopAttrib();
	}
	*/


	/*
	glPushAttrib( GL_LIGHTING_BIT | GL_DEPTH_BITS);
	{
		//glDisable( GL_DEPTH_TEST );
		
		glDisable( GL_LIGHTING );

		//Map.Render();
		Path.Render();

		Drawing3D::Instance().DrawAxes(100.0f, true);

		int x,y;
		Input::Instance().GetMousePosition(&x,&y);
		glColor3f(0.0f,0.0f,1.0f);
		glRasterPos2f(0,0);
		System::Instance().oFont->Print("x:%d y:%d",x,y);
	}
	glPopAttrib();
	*/


	// Pintamos los bounding boxes que al ser translucidos deben ser pintados al final
	// para que dejen ver todo lo que hay detrás
	/*
	glPushAttrib( GL_LIGHTING_BIT | GL_DEPTH_BITS );
	{
		glDisable( GL_LIGHTING );
		glDisable( GL_DEPTH_TEST );
		glDepthMask( GL_FALSE );

		for(ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ObjectItor++)
			(*ObjectItor).RenderBoundingBox();
	}
	glPopAttrib();
	*/
}

#ifdef _WIN32
#define MAX_CONSOLE_LINES 500

void StateGame::RedirectIOToConsole(void)
{
	int hConHandle;
	long lStdHandle;

	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),	&coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
}
#endif


} //namespace Small
