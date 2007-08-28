
#include "player.h"

// PENDIENTE: probablemente estos .h no vayan aquí
#include "../sound/sound.h"
#include "../script/script.h"

namespace Small
{

Player::Player() : Object()
{
	CurrentState = Standing;
	vSpeedJump=5000.0f;
	vSpeedGravity=-50.0f;
	vSpeed=0;
}

// PENDIENTE: ¿mola o no mola pasarle por parámetro el puntero al BSP? Conceptualmente no es correcto
// pero funciona.
void Player::Update(float ElapsedTime, BSP::Q3BSP *Bsp)
{
	// PENDIENTE: usar la velocidad de la entidad.
	// PENDIENTE: hay DOS velocidades diferentes: una la que se le aplica al bicho cuando anda y otra la que lleva el
	// bicho cuando ha saltado, sin necesidad de tocar los controles. Yo me entiendo. Incluso se puede hacer un sistema
	// un pelin mas completo con velocidad y aceleracion.
	float BichoSpeed = 130.0f; // unidades/segundo 
	float RotationSpeed = 270.0f; // grados/segundo 

	float RY = GetRotationY();

	static int LastFrame=0;

	// Es importante que el Object::Update() lo hagamos antes que nada para obtener un Model->GetAnimationState actualizado.
	Object::Update();

	// Hacemos que suenen los pasos
	if( Model->GetCurrentFrame() != LastFrame )
		switch( Model->GetCurrentFrame() )
		{
			case 40:
			case 43:
				SoundManager::Instance().PlayPaso();
				break;
		}
	LastFrame = Model->GetCurrentFrame();

	if( CurrentState == Jumping )
	{
		if( Model->GetAnimationState() == Loop )
			CurrentState = Standing;
	}

	if( CurrentState != Jumping )
	{
		CurrentState = Standing;

		if( Input::Instance().GetKeyState(KeyRight) )
		{
			RY -= RotationSpeed*ElapsedTime;
			CurrentState = Running;
		}
		else if( Input::Instance().GetKeyState(KeyLeft) )
		{
			RY += RotationSpeed*ElapsedTime;
			CurrentState = Running;
		}
		SetRotationY(RY);


		if( Input::Instance().GetKeyState(KeyUp) || Input::Instance().GetKeyState(KeyDown) )
		{
			float Velocity = 0.0f;

			if( Input::Instance().GetKeyState(KeyUp) )
				Velocity = BichoSpeed * ElapsedTime;
			else
				Velocity = -BichoSpeed * ElapsedTime;

			Vector3d dest = this->TryToMove(Velocity, 0);

			// PENDIENTE: hay que calcular el AABB en cada ciclo teniendo en cuenta la rotacion del personaje.
			Vector3d vMin(-25, 1, -25); 
			Vector3d vMax(25, 2, 25);
			
			Vector3d finalDest = Bsp->TraceBox(this->Position, dest, vMin, vMax);
			this->Position = finalDest;

			CurrentState = Running;
		}

		if( Input::Instance().IsKeyPressed(KeySpace) )
		{
			Script::Instance().RaiseEvent("Heroe_OnJump");

			if( CurrentState != Jumping )
			{
				SoundManager::Instance().PlayBoing();
				CurrentState = Jumping;
				vSpeed=vSpeedJump*ElapsedTime;
			}
		}
	}

	Vector3d dest = this->TryToMove(0, 0);
	
	// PENDIENTE: hay que calcular el AABB en cada ciclo teniendo en cuenta la rotacion del personaje.
	Vector3d vMin(-25, 1, -25);
	Vector3d vMax(25, 2, 25);
		
	
	Vector3d finalDest = Bsp->TraceBox(this->Position, dest, vMin, vMax);
	this->Position = finalDest;


	if( CurrentState == Jumping )
	{
		if ( finalDest.GetY()!=dest.GetY() && vSpeed<0)
		{
			vSpeed=vSpeedGravity*ElapsedTime;
			//if( Model->GetAnimationState() == Loop )
				CurrentState = Standing;
		}
		else
			vSpeed+=vSpeedGravity*ElapsedTime;
		
		// this->Move(BichoSpeed*ElapsedTime, 0);
		
		
	}
	else
	{	
		if ( finalDest.GetY()==dest.GetY())
			vSpeed+=vSpeedGravity*ElapsedTime;
		else
			vSpeed=vSpeedGravity*ElapsedTime;
	}
	


	switch( CurrentState )
	{
	case Running:
		this->Model->SetAnim(RUN);
		break;
	case Jumping:
		this->Model->SetAnim(JUMP);
		break;
	default:
		this->Model->SetAnim(STAND);
	}
}

} // namespace Small
