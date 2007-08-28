
#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"
#include "../graphics/drawing3d.h"
#include "../math/vector3d.h"

namespace Small
{
class Camera : public Entity
{
public:
	void Render(void);

	void RotateView(int dx, int dy);
	void RotateView(float angle, float x, float y, float z);

	void Apply(void);
}; // class Camera
} // namespace Small

#endif CAMERA_H
