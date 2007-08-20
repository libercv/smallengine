#include <iostream>

#include "entity.h"

namespace Small
{

Entity::Entity(void)
{
	Path = NULL;
	RotationY = 0;
}

void Entity::Update(void)
{
	if( Path )
		FollowPath();
}

void Entity::SetRotationY(float NewRotationY)
{
	while( NewRotationY > 360 )
		NewRotationY -= 360;

	while( NewRotationY < 0 )
		NewRotationY += 360;

	RotationY = NewRotationY;
}

float Entity::GetRotationY(void)
{
	return RotationY;
}

void Entity::SetPath(WayPath *NewPath)
{
	// Si el Path es null no lo aceptamos
	// PENDIENTE: si no aceptamos un null ¿cómo desasignamos un path para dejar inmovil una entidad?
	if( !NewPath )
		return;

	// Si el path tiene menos de 2 puntos no lo aceptamos
	if( NewPath->Points.size() < 2 )
		return;

	Path = NewPath;
	NextPoint = Path->Points.begin();

	Position.x = (*NextPoint).x;
	Position.y = (*NextPoint).y;
	Position.z = (*NextPoint).z;

	NextPoint++;

	View.x = (*NextPoint).x;
	View.y = (*NextPoint).y;
	View.z = (*NextPoint).z;
}

void Entity::FollowPath(void)
{
	float distance;

	// PENDIENTE: Esta distancia se calcula sobre el vector de trayectoria proyectado sobre el plano XZ.
	// Para Paths con componentes Y!=0 todo esto está más o menos MAL
	distance = sqrt( ((*NextPoint).x - Position.x) * ((*NextPoint).x - Position.x) +
					 ((*NextPoint).z - Position.z) * ((*NextPoint).z - Position.z) );

	if( distance < 1.0f ) // PENDIENTE: sustituir 1.0f por un EPSILON configurable según la escala del mapa
	{
		NextPoint++;

		if( NextPoint == Path->Points.end() )
			NextPoint = Path->Points.begin();

		View.x = (*NextPoint).x;
		View.y = (*NextPoint).y;
		View.z = (*NextPoint).z;
	}
	else
	{
		View.x = (*NextPoint).x;
		View.y = (*NextPoint).y;
		View.z = (*NextPoint).z;

		// PENDIENTE: usar velocidad de la entidad en vez de 1.0f
		Move(1.0f,0.0f);
	}
}

void Entity::Move(float forwardSpeed, float strafeSpeed)
{
	Vector3d fVector,sVector;
	float upVector[3] = {0,1,0}; // PENDIENTE: el upVector no siempre es 0,1,0

	// View.Subtract(Position, fVector);

	fVector.x = cos(RotationY * 3.14f/180.0f);
	fVector.y = 0;
	fVector.z = -sin(RotationY * 3.14f/180.0f);
	
	sVector = fVector.CrossProduct(upVector);
	sVector.Normalize();

    // Adelante y atrás
    Position.x += fVector.x * forwardSpeed;
    Position.y += fVector.y * forwardSpeed;
    Position.z += fVector.z * forwardSpeed;

    View.x += fVector.x * forwardSpeed;
    View.y += fVector.y * forwardSpeed;
    View.z += fVector.z * forwardSpeed;

    // Movimiento lateral
    Position.x -= sVector.x * strafeSpeed;
    Position.z -= sVector.z * strafeSpeed;

    View.x -= sVector.x * strafeSpeed;
    View.z -= sVector.z * strafeSpeed;
}

Vector3d Entity::TryToMove(float forwardSpeed, float strafeSpeed)
{
	Vector3d fVector,sVector;
	float upVector[3] = {0,1,0}; // PENDIENTE: el upVector no siempre es 0,1,0
	Vector3d finalPosition;

	//View.Subtract(Position, fVector);
	//fVector.Normalize();

	fVector.x = cos(RotationY * 3.14f/180.0f);
	fVector.y = 0;
	fVector.z = -sin(RotationY * 3.14f/180.0f);

	sVector = fVector.CrossProduct(upVector);
	sVector.Normalize();

    // Adelante y atrás
    finalPosition.x = Position.x + (fVector.x * forwardSpeed) - (sVector.x * strafeSpeed);
    finalPosition.y = Position.y + (fVector.y * forwardSpeed) - (sVector.y * strafeSpeed);
	finalPosition.z = Position.z + (fVector.z * forwardSpeed) - (sVector.z * strafeSpeed);

	return finalPosition;
}

void Entity::BillboardXZ(Vector3d Target)
{
	Vector3d objToCamProj,objToCam,upAux;
	Vector3d lookAt(0,0,1);

	float angleCosine;

	// objToCamProj es el vector en coordenadas globales que va desde "el que mira"
	// hasta "lo que ve" proyectado en el plano XZ (Y=0) y normalizado.
	Target.Subtract(Position,objToCamProj);
	objToCamProj.y = 0;
	objToCamProj.Normalize();
 
	// Determinamos si el angulo es positivo o negativo
	// Para angulos positivos upAux apuntara en una direccion positiva
	// de lo contrario upAux apuntara hacia abajo, invirtiendo la rotacion
	upAux = lookAt.CrossProduct(objToCamProj);

	// Cuando son paralelos el eje de giro no es 0,0,0 como nos da el producto vectorial, sino 0,1,0 
	if( upAux.x==0 && upAux.y==0 && upAux.z==0 )
		upAux.y=1;
 
	// Calculamos el angulo
	angleCosine = lookAt.DotProduct(objToCamProj);

	// Evitamos posibles problemas de precisión
	if (angleCosine > 1)
		angleCosine = 1;
	else if (angleCosine < -1)
		angleCosine = -1;
	
	// Realizamos el giro de las coordenadas cilíndricas
	glRotatef( acos(angleCosine) * 180.0f/3.14f, upAux.x, upAux.y, upAux.z);
}

void Entity::BillboardXYZ(Vector3d Target)
{
	Vector3d objToCamProj,objToCam,upAux;
	Vector3d lookAt(0,0,1);

	float angleCosine;

	// objToCamProj es el vector en coordenadas globales que va desde "el que mira"
	// hasta "lo que ve" proyectado en el plano XZ (Y=0) y normalizado.
	Target.Subtract(Position,objToCamProj);
	objToCamProj.y = 0;
	objToCamProj.Normalize();
 
	// Determinamos si el angulo es positivo o negativo
	// Para angulos positivos upAux apuntaren una direcci positiva
	// de lo contrario upAux apuntara hacia abajo, invirtiendo la rotacion
	upAux = lookAt.CrossProduct(objToCamProj);

	// Cuando son paralelos el eje de giro no es 0,0,0 como nos da el producto vectorial, sino 0,1,0 
	if( upAux.x==0 && upAux.y==0 && upAux.z==0 )
		upAux.y=1;
 
	// Calculamos el angulo
	angleCosine = lookAt.DotProduct(objToCamProj);

	// Evitamos posibles problemas de precisión
	if (angleCosine > 1)
		angleCosine = 1;
	else if (angleCosine < -1)
		angleCosine = -1;
	
	// Realizamos el giro de las coordenadas cilíndricas
	glRotatef(acos(angleCosine)*180.0f/3.14f, upAux.x, upAux.y, upAux.z);

	// objToCam es el vector normalizado en coordenadas globales que va desde "el que mira" hasta "lo que ve" 
	View.Subtract(Position,objToCam);
	objToCam.Normalize();

	// Calculamos el angulo entre v y v2
	angleCosine =  objToCam.DotProduct(objToCamProj);
	
	// Por si hay problemas de precisión
	if (angleCosine<-1)
		angleCosine=-1;
	else if (angleCosine>1)
		angleCosine=1;
	
	// Realizamos el giro para las coordenadas esféricas vamos a girar según el eje X. Depende de la posición Y
	if( objToCam.y < 0 )
		glRotatef(acos(angleCosine)*180.0f/3.14f,+1,0,0);	
	else
		glRotatef(acos(angleCosine)*180.0f/3.14f,-1,0,0);	
}


} //namespace Small
