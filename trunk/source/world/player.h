#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "../system/input.h"
#include "../graphics/q3bsp.h"

namespace Small
{

typedef enum
{
	Standing=0, Running, Jumping
} PlayerStateEnum;

class Player : public Small::Object
{
private:
	PlayerStateEnum CurrentState;

	float Velocity;

public:
	int Lives, Score;

	Player();
	void Update(float ElapsedTime, BSP::Q3BSP *Bsp);
	void Render(void);
};

} // namespace Small

#endif // PLAYER_H
