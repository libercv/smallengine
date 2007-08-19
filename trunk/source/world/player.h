#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "../system/input.h"

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

public:
	Player();
	void Update(float ElapsedTime);
};

} // namespace Small

#endif // PLAYER_H
