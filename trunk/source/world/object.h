#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"
#include "../graphics/md2.h"
#include "../graphics/drawing3d.h"
#include "../system/timer.h"

typedef enum
{
	X_RIGHT = 0,
	X_MIDDLE = 1,
	X_LEFT = 2,

	Y_TOP = 4,
	Y_MIDDLE = 8,
	Y_BOTTOM = 16,

	Z_NEAR = 32,
	Z_MIDDLE = 64,
	Z_FAR = 128,
} tHotSpot;

namespace Small
{

class Object : public Entity
{
public:
	CMD2Model *Model;
	int HotSpot;

	Object();
	void Update(void);
	void Render(void);
	void RenderBoundingBox(void);
};

} // namespace Small

#endif // OBJECT_H
