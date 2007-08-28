#ifndef ENTITY_H
#define ENTITY_H

// PENDIENTE: sacar todo lo referente a OpenGL de aqui y meter en Graphics.
#ifdef _WIN32
#include <windows.h>
#endif

#include <string>
#include <list>

#include "GL/gl.h"

#include "../math/vector3d.h"
#include "../waymap.h"

namespace Small
{

class Entity
{
private:
	float RotationY;	// Rotaci�n sobre el eje Y (perpendicular al suelo)

public:
	std::string Id;

	// PENDIENTE: no se por que meti esta lista de hijos en entidad. 
	// std::list<Entity *>Children;

	// PENDIENTE: podemos meter una referencia a otra entidad que est� siendo arrastrada/empujada por esta.
	// A lo mejor tambien es interesante otra propiedad que nos indique qu� entidad nos est� arrastrando/empujando
	// creando as� una lista doblemente enlazada donde propagar un empuje y dependiendo de las masas
	// acumuladas y la fricci�n poder o no empujar. �v2.0?

	// PENDIENTE: hay mucha cosa publica aqui. Repasar.

	WayPath *Path;
	vector<WayPoint>::iterator NextPoint;

	Vector3d Position;	// Posicion de la entidad
	Vector3d View;		// Hacia donde esta orientada la entidad (PENDIENTE: si ahora tenemos las rotaciones sobre los ejes esto sobra � no ?)

	void SetRotationY(float NewRotationY);
	float GetRotationY(void);

	Entity(void);

	virtual void Update(void);
	virtual void Render(void) = 0;

	void SetPath(WayPath *NewPath);
	void FollowPath(void);

	// PENDIENTE: renombrar estos m�todos a algo m�s inteligible como Entity.Face(...) y Entity.FaceXZ(...)
	// PENDIENTE: sobrecargar estos m�todos para aceptar tanto un Vector3D como una entidad (y usar la posici�n de la entidad como vector destino)
	void BillboardXZ(Vector3d Target);	
	void BillboardXYZ(Vector3d Target);

	float vSpeed;
	float vSpeedJump;
	float vSpeedGravity;

	void Move(float forwardSpeed, float strafeSpeed);
	Vector3d TryToMove(float forwardSpeed, float strafeSpeed);
};

} // namespace Small

#endif
