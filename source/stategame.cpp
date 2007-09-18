
#include "stategame.h"

#include "xmlParser.h"	// PENDIENTE: ¿en el .h o en el .cpp? Revisar todos.
#include "script/script.h"	// PENDIENTE: 
#include "sound/sound.h"	// PENDIENTE: 
#include <cmath>

namespace Small
{

StateGame::StateGame(void)
{
	// PENDIENTE: cuanto antes saquemos la carga del escenario a un fichero mejor.
	ActiveCamera = 0;

	Bsp.frustum = &Frustum;

	/*
	Player *NewPlayer = new Player();
	NewPlayer->Model = new CMD2Model();
	NewPlayer->Model->LoadModel("resources/models/yoshi.md2");
	NewPlayer->Model->LoadSkin("resources/models/redyoshi.bmp");
	NewPlayer->Model->SetAnim( RUN );
	NewPlayer->Position.Set(416.0f, 0.0f, 0.0f);
	// NewPlayer->Model->ScaleModel( 1.0f );
	// NewPlayer->SetPath( &Path );
	Players.push_back(*NewPlayer);
	*/

	// trigger 1
	Object *NewObject = new Object();
	NewObject->Id = "trigger1";
	NewObject->Position.Set(-70.0f, 10.0f, 0.0f);
	Objects.push_back(*NewObject);

	// trigger 2
	NewObject = new Object();
	NewObject->Id = "trigger2";
	NewObject->Position.Set(10.0f, 10.0f, 0.0f);
	Objects.push_back(*NewObject);

	Light *NewLight = new Light();
	NewLight->Position.Set(320.0f, 64.0f, 64.0f);
	Lights.push_back(*NewLight);
}

void StateGame::CrearBolitas(void)
{
	char *Mapabolitas[] = { "............  ............",
							".    .     .  .     .    .",
							".    .     .  .     .    .", 
							".    .     .  .     .    .", 
							"..........................", 
							".    .  .        .  .    .", 
							".    .  .        .  .    .", 
							"......  ....  ....  ......", 
							"     .     .  .     .     ", 
							"     .     .  .     .     ", 
							"     .              .     ", 
							"     .              .     ", 
							"     .              .     ", 
							"     .              .     ", 
							"     .              .     ", 
							"     .              .     ", 
							"     .              .     ", 
							"     .              .     ", 
							"     .     .  .     .     ",
							"     .     .  .     .     ", 
							"......  ....  ....  ......", 
							".    .  .        .  .    .", 
							".    .  .        .  .    .", 
							"..........................", 
							".    .     .  .     .    .", 
							".    .     .  .     .    .", 
							".    .     .  .     .    .", 
							"............  ............" };

	for( char y=0; y<28; y++)
		for( char x=0; x<26; x++)
		{
			if( *(Mapabolitas[y]+x) == '.' )
			{
				char nombre[256];
				sprintf(nombre, "bola%d\0", y*30+x);
				Object *NewObject = new Object();
				NewObject->Id = nombre;
				NewObject->Position.Set(x*32.0f - 120.0f, 10.0f, y*28.0f - 180.0f);
				Objects.push_back(*NewObject);
			}
		}
}

EngineStateEnum StateGame::Update(float ElapsedTime)
{
	EngineStateEnum NextState = Game;
	static float dt=0;

	/*
	int dx,dy;
	Input::Instance().GetMouseMotion(&dx,&dy);
	Cameras[iCamera].RotateView(dx,dy);
	*/

	/*
	mouse = CTextureManager::GetInstance()->LoadTexture("resources/textures/mouse.tga");
	mouseMask = CTextureManager::GetInstance()->LoadTexture("resources/textures/mouseMask.tga");
	*/

	// PENDIENTE: la pausa se debe implementar como otro estado más.
	if( Engine::Instance().CurrentState == Pause )
	{
		if( Input::Instance().IsKeyPressed(KeyPause) )
			Engine::Instance().CurrentState = Game;
	}
	else
	{
		dt += ElapsedTime;

		// Propagamos el Update a todos los jugadores
		for(vector<Player>::iterator PlayerItor=Players.begin(); PlayerItor!=Players.end(); PlayerItor++)
		{
			(*PlayerItor).Update(ElapsedTime, &Bsp);

			if( dt >= 0.1f )
			{
				(*PlayerItor).Score -= 1;
			}

			// Chequeo de colisiones
			// PENDIENTE: cada instancia puede tener su propio radio
			float Radio = 10.0f;
			Vector3d Distancia;

			for(vector<Object>::iterator ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ObjectItor++)
			{
				if( !(*ObjectItor).Deleted )
				{
					(*ObjectItor).Position.Subtract((*PlayerItor).Position, Distancia);

					if( abs(Distancia.GetLength()) < Radio*2 )
					{
						char evento[256];
						sprintf(evento, "%s_OnCollision\0", (*PlayerItor).Id.c_str());
						Script::Instance().RaiseEvent(evento, (char *)(*ObjectItor).Id.c_str());
					}
				}
			}
		}

		if( dt >= 0.1f )
		{
			dt = 0;
		}

		// Propagamos el Update a todos los objetos
		for(vector<Object>::iterator ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ObjectItor++)
		{
			if( !(*ObjectItor).Deleted )
				(*ObjectItor).Update();
		}

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
		else if( Input::Instance().IsKeyPressed(KeyHome) )
			Players[0].Position.Set(0.0f, 10.0f, 0.0f);
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

		if( Input::Instance().GetKeyState(KeyPgUp) )
		{
			Cameras[ActiveCamera].Position.y += speed * ElapsedTime;
			Cameras[ActiveCamera].View.y += speed * ElapsedTime;
		}
		else if( Input::Instance().GetKeyState(KeyPgDown) )
		{
			Cameras[ActiveCamera].Position.y -= speed * ElapsedTime;
			Cameras[ActiveCamera].View.y -= speed * ElapsedTime;
		}


		if( Input::Instance().GetKeyState(KeySupr) )
		{
			Cameras[ActiveCamera].Position.z += speed * ElapsedTime;
			Cameras[ActiveCamera].View.z += speed * ElapsedTime;
		}
		else if( Input::Instance().GetKeyState(KeyInsert) )
		{
			Cameras[ActiveCamera].Position.z -= speed * ElapsedTime;
			Cameras[ActiveCamera].View.z -= speed * ElapsedTime;
		}


		/*
		if( fSpeed || sSpeed )
		{
			Vector3d dest = Cameras[ActiveCamera].TryToMove(fSpeed, sSpeed);

			// PENDIENTE: obtener el bounding box de la entidad/objeto
			Vector3d vMax(10, 0, 10);
			Vector3d vMin(-10,-50,-10);

			//Vector3d finalDest= Bsp.TraceSphere(orig, dest, 50);
			Vector3d finalDest = Bsp.TraceBox(Cameras[0].Position, dest, vMin, vMax);

			// PEDNDIENTE: no usar los accesors para miembros atómicos. Mejor pasar un vector3d
			// o usar directamente los miembros
			// Cameras[0].Position = finalDest;
		}
		*/
		// ********************************************************************

	}

	// Hacemos que la cámara mire al bicho
	/*
	Vector3d fVector, fView;

	fVector.x = cos(Players[0].GetRotationY() * 3.14f/180.0f);
	fVector.y = 0;
	fVector.z = -sin(Players[0].GetRotationY() * 3.14f/180.0f);

	fVector.Add(Players[0].Position, fView);

	Cameras[1].Position = Players[0].Position;
	Cameras[1].View = fView;

	Cameras[1].Position.y += 30;
	Cameras[1].View.y += 30;
	*/


	/*
	Cameras[0].View = Players[0].Position;

	Cameras[1].Position = Players[0].Position;
	Cameras[1].Position.x += 200.0f;
	Cameras[1].Position.y = 60.0f;
	Cameras[1].View = Players[0].Position;
	*/

	return NextState;
}

void StateGame::Render(void)
{
	// PENDIENTE: ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ DE AQUI VA CASI TODO FUERA !!!!!!!!!!!!!!!!!!!!!!!!!

	// PENDIENTE: todo lo que se llame gl* Drawing3D. 

	Drawing3D::Instance().Clear();
	Drawing3D::Instance().PerspectiveMode(Window::Instance().GetWidth(), Window::Instance().GetHeight());

	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glColor3f(1.0f, 1.0f, 1.0f);

	Cameras[ActiveCamera].Apply();

	glPushAttrib( GL_POLYGON_BIT );
	{
		// PENDIENTE: esto no mola. Si hace falta convertir los polígonos del BSP
		// se convierten en la carga y si no adoptamos el mismo sistema de referencia
		// que usa el BSP (que creo que es el mismo que el de los MD2)
		// PENDIENTE: de todas formas, he comentado glFrontFace( GL_CW ); y sigue viéndose todo.
		// glFrontFace( GL_CW );

		//Cameras[1].Apply();
		Frustum.CalculateFrustum();
		//Cameras[0].Apply();
		Bsp.RenderLevel(Cameras[ActiveCamera].Position);
	}
	glPopAttrib();

	
/*
	// PENDIENTE: Retirado hasta que este bien probado
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
		if( !(*ObjectItor).Deleted )
			(*ObjectItor).Render();

	// Pintamos las cámaras
	for(vector<Camera>::size_type i=0; i<Cameras.size(); i++)
		if( i != ActiveCamera )
			Cameras[i].Render();

	// Pintamos las luces
	for(vector<Light>::iterator LightItor=Lights.begin(); LightItor!=Lights.end(); LightItor++)
		(*LightItor).Render();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Path.Render();

	Drawing3D::Instance().OrthoMode(0,0, Window::Instance().GetWidth(), Window::Instance().GetHeight());

	/*
	int x,y;
	Input::Instance().GetMousePosition(&x, &y);

	float mouseX1,mouseY1, mouseX2,mouseY2;

	mouseX1 = (float)x;
	mouseY1 = (float)y;
	mouseX2 = (float)x+31;
	mouseY2 = (float)y+31;

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
	*/

	// PENDIENTE: pasar al Print la posicion y el color de la fuente por parámetros.
	glColor3f(0.5f, 1.0f, 1.0f);

	float pos=30;
	for(vector<Player>::iterator PlayerItor=Players.begin(); PlayerItor!=Players.end(); PlayerItor++)
	{
		glRasterPos2f(10.0f, pos+=30);
		Drawing3D::Instance().BigFont->Print("%s Score: %d Lives: %d ", (*PlayerItor).Id.c_str(), (*PlayerItor).Score, (*PlayerItor).Lives);
	}


	/*
	glRasterPos2f(10.0f, 30.0f);
	Drawing3D::Instance().BigFont->Print("%f %f %f", Players[0].Position.x, Players[0].Position.y, Players[0].Position.z );

	glRasterPos2f(10.0f, 60.0f);
	Drawing3D::Instance().BigFont->Print("fps = %d", Timer::Instance().GetFps());
	*/

	/*
	glRasterPos2f(10.0f, (float)Window::Instance().GetHeight()-50);
	Drawing3D::Instance().BigFont->Print("Height = %d", Window::Instance().GetHeight());

	//glRasterPos2f(10.0f, (float)Window::Instance().GetHeight()-25);
	//Drawing3D::Instance().BigFont->Print("X=%f  Y=%f", mouseX1,mouseY1);

	glRasterPos2f(10.0f, (float)Window::Instance().GetHeight());
	Drawing3D::Instance().BigFont->Print("RotationY = %f", Players[0].GetRotationY());

	Drawing3D::Instance().PerspectiveMode(Window::Instance().GetWidth(), Window::Instance().GetHeight());
	*/
	
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
		// System::Instance().oFont->Print("x:%d y:%d",x,y);
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

void StateGame::KillPlayer(char *PlayerId)
{
	for(vector<Player>::iterator PlayerItor=Players.begin(); PlayerItor!=Players.end(); PlayerItor++)
		if( !strcmp((*PlayerItor).Id.c_str(), PlayerId) )
		{
			SoundManager::Instance().PlayPlayerDead();
			(*PlayerItor).Position.Set(0.0f, 10.0f, 0.0f);
			(*PlayerItor).SetRotationY(0.0f);
			(*PlayerItor).Lives--;
			break;
		}
}

void StateGame::KillObject(char *PlayerId, char *ObjectId)
{
	for(vector<Player>::iterator PlayerItor=Players.begin(); PlayerItor!=Players.end(); PlayerItor++)
		if( !strcmp((*PlayerItor).Id.c_str(), PlayerId) )
		{
 			for(vector<Object>::iterator ObjectItor=Objects.begin(); ObjectItor!=Objects.end(); ++ObjectItor)
				if( !strcmp((*ObjectItor).Id.c_str(), ObjectId) )
				{
					SoundManager::Instance().PlayBola();

					(*ObjectItor).Deleted = true;	// PENDIENTE: Deleted no deberia ser publica

					// PENDIENTE: así se borra un item de un vector
					// delete (*itor);
					// itor = m_texlist.erase( itor );
					
					(*PlayerItor).Score += 10;
					break;
				}			

			break;
		}
}

void StateGame::SetActiveCamera(int NewActiveCamera)
{
	if( NewActiveCamera<0 || NewActiveCamera>1 )
		return;

	ActiveCamera = NewActiveCamera;
}


void StateGame::LoadLevel(char *NewLevel)
{
	char name[256];
	int i;

	ClearLevel();

	sprintf(name, "resources/levels/%s\0", NewLevel);

	XMLNode xMainNode=XMLNode::openFileHelper(name);

	// PENDIENTE: ¡¡¡ comprobaciones por un tubo !!! (una por cada dato crítico)
	XMLNode NodeLevel=xMainNode.getChildNode("level");

	// PENDIENTE: controlar que se carga bien el BSP. 
	Bsp.LoadBSP(NodeLevel.getChildNode("bsp").getAttribute("file")); 

	// Cargamos los paths
	XMLNode NodePaths=NodeLevel.getChildNode("paths");
    int NumberOfPaths=NodePaths.nChildNode("path");

	Log::Instance().Write("paths: %d", NumberOfPaths);
    
    for(i=0; i<NumberOfPaths; i++)
	{
		XMLNode NodePath = NodePaths.getChildNode("path", i);
		int NumberOfPoints = NodePath.nChildNode("waypoint");

		Log::Instance().Write("points: %d", NumberOfPoints);

		WayPath *NewPath = new WayPath();
		NewPath->Id = NodePath.getAttribute("id");

		for(int j=0; j<NumberOfPoints; j++)
		{
			XMLNode NodeWaypoint = NodePath.getChildNode("waypoint", j);
			NewPath->Points.push_back( WayPoint((float)atof(NodeWaypoint.getAttribute("x")), (float)atof(NodeWaypoint.getAttribute("y")), (float)atof(NodeWaypoint.getAttribute("z"))) );
		}

		Paths.push_back(*NewPath);
	}
	

	// Cargamos a los jugadores
	XMLNode NodePlayers=NodeLevel.getChildNode("players");
	int NumberOfPlayers=NodePlayers.nChildNode("player");

	Log::Instance().Write("players: %d", NumberOfPlayers);

	for( i=0; i<NumberOfPlayers; i++)
	{
		XMLNode NodePlayer=NodePlayers.getChildNode("player", i);

		Player *NewPlayer = new Player();
		NewPlayer->Id = NodePlayer.getAttribute("id");
		NewPlayer->Score = 0;
		NewPlayer->Lives = 3;
		NewPlayer->Model = new CMD2Model();
		NewPlayer->Model->LoadModel(NodePlayer.getChildNode("model").getAttribute("file"));
		NewPlayer->Model->LoadSkin((char *)NodePlayer.getChildNode("skin").getAttribute("file"));
		NewPlayer->Model->SetAnim( RUN );	// PENDIENTE: leer la animación desde el fichero XML
		NewPlayer->Position.Set((float)atof(NodePlayer.getChildNode("position").getAttribute("x")), (float)atof(NodePlayer.getChildNode("position").getAttribute("y")), (float)atof(NodePlayer.getChildNode("position").getAttribute("z")));
		Players.push_back(*NewPlayer);
	}

	// Cargamos a los malos
	XMLNode NodeEnemies=NodeLevel.getChildNode("enemies");
    int NumberOfEnemies=NodeEnemies.nChildNode("enemy");

	Log::Instance().Write("enemigos: %d", NumberOfEnemies);
    
    for(i=0; i<NumberOfEnemies; i++)
	{
		XMLNode NodeEnemy = NodeEnemies.getChildNode("enemy", i);
		Object *NewObject = new Object();
		NewObject->Id = NodeEnemy.getAttribute("id");
		NewObject->Model = new CMD2Model();
		NewObject->Model->LoadModel(NodeEnemy.getChildNode("model").getAttribute("file"));
		NewObject->Model->LoadSkin((char *)NodeEnemy.getChildNode("skin").getAttribute("file"));
		NewObject->Model->SetAnim( CROUCH_WALK );	// PENDIENTE


		for(vector<WayPath>::iterator PathItor=Paths.begin(); PathItor!=Paths.end(); PathItor++)
			if( !strcmp((*PathItor).Id.c_str(), NodeEnemy.getAttribute("path")) )
			{
				NewObject->SetPath( &(*PathItor) );
				break;
			}

		// PENDIENTE: asignar velocidad, controlador, etc...
		Objects.push_back(*NewObject);
	}


	// Cargamos las cámaras
	XMLNode NodeCameras=NodeLevel.getChildNode("cameras");
    int NumberOfCameras=NodeCameras.nChildNode("camera");

	Log::Instance().Write("camaras: %d", NumberOfCameras);

    for(i=0; i<NumberOfCameras; i++)
	{
		XMLNode NodeCamera = NodeCameras.getChildNode("camera", i);
		Camera *NewCamera = new Camera();
		NewCamera->Id = NodeCamera.getAttribute("id");
		NewCamera->Position.Set((float)atof(NodeCamera.getChildNode("position").getAttribute("x")), (float)atof(NodeCamera.getChildNode("position").getAttribute("y")), (float)atof(NodeCamera.getChildNode("position").getAttribute("z")));
		Cameras.push_back(*NewCamera);
	}

	xMainNode=XMLNode::emptyNode();
}

void StateGame::ClearLevel(void)
{
 	Bsp.Destroy();
	Objects.clear();
	Cameras.clear();
	// Lights.clear();
	Players.clear();
	Paths.clear();
}

} //namespace Small
