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
	float RotationY;	// Rotación sobre el eje Y (perpendicular al suelo)

public:
	std::string Id;

	// PENDIENTE: no se por que meti esta lista de hijos en entidad. 
	// std::list<Entity *>Children;

	// PENDIENTE: podemos meter una referencia a otra entidad que esté siendo arrastrada/empujada por esta.
	// A lo mejor tambien es interesante otra propiedad que nos indique qué entidad nos está arrastrando/empujando
	// creando así una lista doblemente enlazada donde propagar un empuje y dependiendo de las masas
	// acumuladas y la fricción poder o no empujar. ¿v2.0?

	// PENDIENTE: hay mucha cosa publica aqui. Repasar.

	// PENDIENTE: implementar una clase WayWalker o algo así, que implemente lo necesario para
	// recorrer un path y derivar esta clase de esa.
	WayPath *Path;
	vector<WayPoint>::iterator NextPoint;

	Vector3d Position;	// Posicion de la entidad

	// PENDIENTE: si ahora tenemos las rotaciones sobre los ejes esto sobra ¿ no ?
	Vector3d View;		// Hacia donde esta orientada la entidad

	void SetRotationY(float NewRotationY);
	float GetRotationY(void);

	Entity(void);

	virtual void Update(void);
	virtual void Render(void) = 0;

	void SetPath(WayPath *NewPath);
	void FollowPath(void);

	// PENDIENTE: renombrar estos métodos a algo más inteligible como Entity.Face(...) y Entity.FaceXZ(...)
	// PENDIENTE: sobrecargar estos métodos para aceptar tanto un Vector3D como una entidad (y usar la posición de la entidad como vector destino)
	// PENDIENTE: estos métodos acaban usando código de OpenGL. Supongo que hay que rediseñarlos para que al llamarlos
	// se recalculen los ángulos de rotación sobre los 3 ejes y nada más. A la hora de hacer el render ya se harán
	// los GlRotate();
	void BillboardXZ(Entity *Target);
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
