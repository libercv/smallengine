#ifndef LIGHT_H
#define LIGHT_H

#include "entity.h"

#include "../graphics/drawing3d.h"

namespace Small
{

class Light : public Entity
{
	// PENDIENTE: revisar la asignación de nombres de luz
private:
	static int LIGHT_NAME_CNT;

	int LIGHT_NAME;

public:
	bool On;

	Light(void);

	void Update(void);
	void Render(void);
};

#endif // LIGHT_H

} // namespace Small
