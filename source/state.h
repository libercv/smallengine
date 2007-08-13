#ifndef STATE_H
#define STATE_H

// PENDIENTE: cada estado debe ser singleton pero esta clase, al ser abstracta, no puede implementar 
// el patrón. ¿Como lo hacemos para no tener que repetir patrón en todas las clases?

namespace Small
{
virtual class State
{
public:
	enum StateId
	{
		//Intro = 0, Menu, Game, Pause, Scores, Credits, Done
		Menu, Game, Pause, Done
	};

	virtual StateId Update(float ElapsedTime) = 0;
	virtual void Render(void) = 0;
};
} // namespace Small

#endif // STATE_H
