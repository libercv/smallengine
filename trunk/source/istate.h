#ifndef STATE_H
#define STATE_H

#include "singleton.h"

namespace Small
{
typedef enum
{
	Menu=0, Game, Pause, Done
} EngineStateEnum;

class IState
{
public:
	virtual EngineStateEnum Update(float ElapsedTime) = 0;
	virtual void Render(void) = 0;
};
} // namespace Small

#endif // STATE_H
