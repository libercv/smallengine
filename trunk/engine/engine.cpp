
#include "engine.h"

namespace Small
{

Engine::Engine(void)
{
	Object *NewObject;
	Camera *NewCamera;
	Light *NewLight;

	iCamera = 0;

	Bsp.frustum = &Frustum;
	Bsp.LoadBSP("resources/maps/Tutorial.bsp");

	NewObject = new Object();
	NewObject->Model = new CMD2Model();
	NewObject->Model->LoadModel( "resources/models/yoshi.md2" );
	NewObject->Model->LoadSkin( "resources/models/yoshi.bmp" );
	NewObject->Model->SetAnim( RUN );
	NewObject->Model->ScaleModel( 4.0f );
	NewObject->SetPath( &Path );
	Objects.push_back(*NewObject);

	for(short a=0; a<3; a++)
	{
		NewCamera = new Camera();
		NewCamera->Position.x = (float)(sin(a * 2 * 3.14 / 10) * 10);
		NewCamera->Position.y = (float)(4 + sin(a * 4 * 3.14 / 10) * 2);
		NewCamera->Position.z = (float)(cos(a * 2 * 3.14 / 10) * 10);

		Cameras.push_back(*NewCamera);
	}

	for(short a=0; a<1; a++)
	{
		NewLight = new Light();
		NewLight->SetPath( &Path );
		Lights.push_back(*NewLight);
	}

	Cameras[0].Position.x = -5;
	Cameras[0].Position.y = 200;
	Cameras[0].Position.z = 0;

	// PENDIENTE: ¿ por qué no sigue la cámara el path ?
	//Cameras[0].SetPath( &Path );

	Cameras[1].Position.x = 928;
	Cameras[1].Position.y = 256;
	Cameras[1].Position.z = 720;

	Cameras[2].Position.x = -952;
	Cameras[2].Position.y = 256;
	Cameras[2].Position.z = -760;
}

void Engine::Update(void)
{

	vector<Object>::iterator ObjectItor;
	vector<Light>::iterator LightItor;

	float fSpeed, sSpeed;

	int dx,dy;
	Input::Instance().GetMouseMotion(&dx,&dy);
	Cameras[iCamera].RotateView(dx,dy);

	// PENDIENTE: la pausa se debe implementar como otro estado más.
	if( Game::Instance().State == StatePause )
	{
		if( Input::Instance().IsKeyPressed(KeyPause) )
			Game::Instance().State = StateGame;
	}
	else
	{
		fSpeed = sSpeed = 0;

		Lights[0].Position.y = 150;

		for(ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ObjectItor++)
			(*ObjectItor).Update();

		for(LightItor=Lights.begin(); LightItor!=Lights.end(); LightItor++)
			(*LightItor).Update();

		if( Input::Instance().IsKeyPressed(KeyEscape) )
			Game::Instance().State = StateMenu;
		else if( Input::Instance().IsKeyPressed(KeyPause) )
			Game::Instance().State = StatePause;
		else if( Input::Instance().IsKeyPressed(KeySpace) )
			iCamera = (++iCamera) % 3;
		else if( Input::Instance().GetKeyState(KeyHome) )
		{
			Cameras[0].Position.y += 3;
			Cameras[0].View.y += 3;
		}
		else if( Input::Instance().GetKeyState(KeyEnd) )
		{
			Cameras[0].Position.y -= 3;
			Cameras[0].View.y -= 3;
		}
		else if( Input::Instance().IsKeyPressed(KeyReturn) )
		{
			Lights[0].On = !Lights[0].On;
			//Objects[2].Model->SetAnim( ++anim );

			/*
			Objects[0].Model->m_anim.curr_frame++;
			Objects[1].Model->m_anim.curr_frame++;
			Objects[2].Model->m_anim.curr_frame++;
			*/
		}

		// PENDIENTE: usar la velocidad de la entidad
		float speed=2.50;
		if( Input::Instance().GetKeyState(KeyUp) )
			// PENDIENTE: usar la velocidad de la entidad
			fSpeed = 3.0f;
		else if( Input::Instance().GetKeyState(KeyDown) )
			// PENDIENTE: usar la velocidad de la entidad
			fSpeed = -3.0f;

		if( Input::Instance().GetKeyState(KeyLeft) )
			// PENDIENTE: usar la velocidad de la entidad
			sSpeed = 3.0f;
		else if( Input::Instance().GetKeyState(KeyRight) )
			// PENDIENTE: usar la velocidad de la entidad
			sSpeed = -3.0f;

		if( fSpeed || sSpeed )
		{
			// PENDIENTE: usar la velocidad de la entidad
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
	}

	//Cameras[1].View = Objects[0].Position;
	Small::Vector3d origen(0,0,0);
	Cameras[1].BillboardXYZ(origen);
	Cameras[2].View = Objects[0].Position;
}

void Engine::Render(void)
{
	vector<Object>::iterator ObjectItor;
	vector<Camera>::iterator CameraItor;
	vector<Light>::iterator LightItor;

	// PENDIENTE: todo esto va en graphics. 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// PENDIENTE: Esto solo se debe hacer cuando se redimensione la ventana, cuando pasemos entre
	// Ortho y perspective y cuando redimensionemos el �ea de render (modo edici�) si? no?
	if( iCamera == 0 )
		gluPerspective(45.0f,(GLfloat)Window::Instance().GetWidth()/ (GLfloat)Window::Instance().GetHeight(), .5f, 65535.0f);
	else
		gluPerspective(100.0f,(GLfloat)Window::Instance().GetWidth()/ (GLfloat)Window::Instance().GetHeight(), .5f, 65535.0f);
		//glOrtho(-10,10,-10,10,0.1,20);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Cameras[iCamera].Look();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

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
	// Pintamos las luces
	for(LightItor=Lights.begin(); LightItor!=Lights.end(); LightItor++)
		(*LightItor).Render();

	// Pintamos las c�aras (solo habr�que hacerlo en modo edici�).
	for(std::vector<Small::Camera>::size_type i=0; i<Cameras.size(); i++)
	{
		if( i != iCamera )
			Cameras[i].Render();
	}

	// Pintamos los Objetos
	for(ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ObjectItor++)
		(*ObjectItor).Render();
	
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

} //namespace Small
