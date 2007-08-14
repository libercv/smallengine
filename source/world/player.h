#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "../system/input.h"

namespace Small
{

class Player : public Small::Object
{
private:

public:
	void Update(float ElapsedTime);
};

} // namespace Small

#endif // PLAYER_H
