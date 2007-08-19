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
public:
	std::string Id;
	std::list<Entity *>Children;

	WayPath *Path;
	vector<WayPoint>::iterator NextPoint;

	Vector3d Position, View;

	Entity(void);

	virtual void Update(void);
	virtual void Render(void) = 0;

	void SetPath(WayPath *NewPath);
	void FollowPath(void);

	void BillboardXZ(Vector3d Target);
	void BillboardXYZ(Vector3d Target);

	void Move(float forwardSpeed, float strafeSpeed);
	Vector3d TryToMove(float forwardSpeed, float strafeSpeed);
};

} // namespace Small

#endif
