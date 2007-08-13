
#include "stateGame.h"

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

	Object *NewObject = new Object();
	NewObject->Model = new CMD2Model();
	NewObject->Model->LoadModel( "resources/models/yoshi.md2" );
	NewObject->Model->LoadSkin( "resources/models/yoshi.bmp" );
	NewObject->Model->SetAnim( RUN );
	// NewObject->Model->ScaleModel( 1.0f );
	// NewObject->SetPath( &Path );
	Objects.push_back(*NewObject);

	Camera *NewCamera = new Camera();
	NewCamera->Position.x = 300;
	NewCamera->Position.y = 100;
	NewCamera->Position.z = 300;
	//NewCamera->SetPath( &Path );
	Cameras.push_back(*NewCamera);

	/*
	for(short a=0; a<1; a++)
	{
		Light *NewLight = new Light();
		NewLight->SetPath( &Path );
		Lights.push_back(*NewLight);
	}
	*/
}

State::StateId StateGame::Update(float ElapsedTime)
{
	State::StateId NextState = State::StateId::Game;

	int dx,dy;

	Input::Instance().GetMouseMotion(&dx,&dy);

	Cameras[iCamera].RotateView(dx,dy);

	// PENDIENTE: la pausa se debe implementar como otro estado más.
	if( Engine::Instance().CurrentState == Pause )
	{
		if( Input::Instance().IsKeyPressed(KeyPause) )
			Engine::Instance().CurrentState = Game;
	}
	else
	{
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
			NextState = State::StateId::Menu;
			// Engine::Instance().CurrentState = State::StateId::Menu;	// PENDIENTE: desde aquí no debemos cambiar el state de Game. Lo devolveremos como retorno.
		}
		else if( Input::Instance().IsKeyPressed(KeyPause) )
		{
			NextState = State::StateId::Pause;
			//Engine::Instance().CurrentState = State::StateId::Pause; // PENDIENTE: desde aquí no debemos cambiar el state de Game. Lo devolveremos como retorno.
		}
		else if( Input::Instance().IsKeyPressed(KeySpace) )
			iCamera = (++iCamera) % Cameras.size();
		else if( Input::Instance().IsKeyPressed(KeyReturn) )
		{
			// Lights[0].On = !Lights[0].On;
		}


		// *** PRUEBAS: movemos al bicho ***************************************
		float BichoSpeed = 130.0f; // unidades/segundo // PENDIENTE: usar la velocidad de la entidad.
		Objects[0].Position.x += -(BichoSpeed*ElapsedTime);
		if( Objects[0].Position.x < 0.0f ) 
			Objects[0].Position.x = 800.0f;
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

		if( Input::Instance().GetKeyState(KeyUp) )
			fSpeed = speed * ElapsedTime;
		else if( Input::Instance().GetKeyState(KeyDown) )
			fSpeed = -1 * speed * ElapsedTime;

		if( Input::Instance().GetKeyState(KeyLeft) )
			sSpeed = speed * ElapsedTime;
		else if( Input::Instance().GetKeyState(KeyRight) )
			sSpeed = -1 * speed * ElapsedTime;

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
			Cameras[0].SetPosition( finalDest );
		}
		// ********************************************************************

	}

	// Hacemos que la cámara mire al bicho
	Cameras[0].View = Objects[0].Position;

	/*
	Vector3d origen(0,0,0);
	Cameras[1].BillboardXYZ(origen);
	Cameras[2].View = Objects[0].Position;
	*/

	return NextState;
}

void StateGame::Render(void)
{

	// PENDIENTE:
	// ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ DE AQUI VA CASI TODO FUERA !!!!!!!!!!!!!!!!!!!!!!!!!


	// PENDIENTE: todo esto va en graphics. 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// PENDIENTE: Esto solo se debe hacer cuando se redimensione la ventana, cuando pasemos entre
	// Ortho y Perspective y cuando redimensionemos el área de render (modo edición) ¿si,no?
	if( iCamera == 0 )
		gluPerspective(45.0f,(GLfloat)Window::Instance().GetWidth()/ (GLfloat)Window::Instance().GetHeight(), .5f, 65535.0f);
	else
		gluPerspective(100.0f,(GLfloat)Window::Instance().GetWidth()/ (GLfloat)Window::Instance().GetHeight(), .5f, 65535.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Cameras[iCamera].Look();

	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);

	//Drawing3D::Instance().DrawSkyBox(0,-0.0001,0,400,200,400);
	//Drawing3D::Instance().DrawFloor();

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
