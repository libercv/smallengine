#ifndef STATE_H
#define STATE_H

#include "singleton.h"

namespace Small
{
typedef enum
{
	//Intro = 0, Menu, Game, Pause, Scores, Credits, Done
	Menu, Game, Pause, Done
} StateEnum;

class IState
{
public:
	virtual StateEnum Update(float ElapsedTime) = 0;
	virtual void Render(void) = 0;
};
} // namespace Small

#endif // STATE_H
