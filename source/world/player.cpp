
#include "player.h"

namespace Small
{

Player::Player() : Object()
{
	CurrentState = Standing;
}

// PENDIENTE: ¿mola o no mola pasarle por parámetro el puntero al BSP? Conceptualmente no es correcto
// pero funciona.
void Player::Update(float ElapsedTime, BSP::Q3BSP *Bsp)
{
	// PENDIENTE: usar la velocidad de la entidad.
	// PENDIENTE: hay DOS velocidades diferentes: una la que se le aplica al bicho cuando anda y otra la que lleva el
	// bicho cuando ha saltado, sin necesidad de tocar los controles. Yo me entiendo. Incluso se puede hacer un sistema
	// un pelin mas completo con velocidad y aceleracion.
#ifdef _WIN32
	float BichoSpeed = 130.0f; // unidades/segundo 
	float RotationSpeed = 270.0f; // grados/segundo 
#else
	float BichoSpeed = 1.30f; // unidades/segundo 
	float RotationSpeed = 0.5f; // grados/segundo 
#endif

	float RY = GetRotationY();

	// Es importante que el Object::Update() lo hagamos antes que nada para obtener un Model->GetAnimationState actualizado.
	Object::Update();

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
			// this->Position.x+=BichoSpeed*ElapsedTime;
			RY -= RotationSpeed*ElapsedTime;
			CurrentState = Running;
		}
		else if( Input::Instance().GetKeyState(KeyLeft) )
		{
			// this->Position.x-=BichoSpeed*ElapsedTime;
			RY += RotationSpeed*ElapsedTime;
			CurrentState = Running;
		}
		SetRotationY(RY);

		if( Input::Instance().GetKeyState(KeyUp) )
		{
			// this->Move(BichoSpeed*ElapsedTime, 0);

			Vector3d dest = this->TryToMove(BichoSpeed*ElapsedTime, 0);

			// PENDIENTE: hay que calcular el AABB en cada ciclo teniendo en cuenta la rotacion del personaje.
			Vector3d vMin(-25, 1, -25);
			Vector3d vMax(25, 2, 25);
			
			Vector3d finalDest = Bsp->TraceBox(this->Position, dest, vMin, vMax);
			this->Position = finalDest;

			CurrentState = Running;
		}
		else if( Input::Instance().GetKeyState(KeyDown) )
		{
			this->Move(-BichoSpeed*ElapsedTime, 0);
			CurrentState = Running;
		}

		if( Input::Instance().GetKeyState(KeySpace) )
		{
			if( CurrentState != Jumping )
			{
				CurrentState = Jumping;
			}
		}
	}

	// PENDIENTE: Orientar al personaje

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
