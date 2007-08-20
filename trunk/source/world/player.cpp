
#include "player.h"

namespace Small
{

Player::Player() : Object()
{
	CurrentState = Standing;
}

void Player::Update(float ElapsedTime)
{
	// PENDIENTE: usar la velocidad de la entidad.
	// PENDIENTE: hay DOS velocidades diferentes: una la que se le aplica al bicho cuando anda y otra la que lleva el
	// bicho cuando ha saltado, sin necesidad de tocar los controles. Yo me entiendo. Incluso se puede hacer un sistema
	// un pel�n m�s completo con velocidad y aceleraci�n.
#ifdef WIN32
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
			RY += RotationSpeed*ElapsedTime;
			CurrentState = Running;
		}
		else if( Input::Instance().GetKeyState(KeyLeft) )
		{
			// this->Position.x-=BichoSpeed*ElapsedTime;
			RY -= RotationSpeed*ElapsedTime;
			CurrentState = Running;
		}
		SetRotationY(RY);

		if( Input::Instance().GetKeyState(KeyUp) )
		{
			this->Move(BichoSpeed*ElapsedTime, 0);
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
