
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

	void Look(void);
};

} // namespace Small
