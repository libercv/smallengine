
#include "player.h"

namespace Small
{

void Player::Update(float ElapsedTime)
{
	// PENDIENTE: usar la velocidad de la entidad.
	float BichoSpeed = 130.0f; // unidades/segundo 

	if( Input::Instance().GetKeyState(KeyRight) )
		this->Position.x+=BichoSpeed*ElapsedTime;
	else if( Input::Instance().GetKeyState(KeyLeft) )
		this->Position.x-=BichoSpeed*ElapsedTime;

	// PENDIENTE:
	//
	// - Orientar al personaje
	// - Aplicarle la animación adecuada dependiendo de si anda, salta, está parado, etc.
	
	Object::Update();
}


} // namespace Small
