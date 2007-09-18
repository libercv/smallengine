
#ifndef IINPUT_H
#define IINPUT_H

// Enumeración de las teclas que puede usar el motor
// Seguramente esto vaya en otro archivo de cabecera
// Algo asi como inputenums.h
enum Keys
{
	P1KeyDown=0,
	P1KeyUp,
	P1KeyRight,
	P1KeyLeft,
	P1KeyJump,

	P2KeyDown,
	P2KeyUp,
	P2KeyRight,
	P2KeyLeft,
	P2KeyJump,

	KeyEscape,
	KeyReturn,
	KeyPause,
	KeyEnd,
	KeyHome,
	KeyPgUp,
	KeyPgDown,
	KeyInsert,
	KeySupr,
	MAX_KEYS
};
enum MouseButtons {MouseButtonLeft, MouseButtonRight, MouseButtonMiddle};

class IInput
{
public:
	virtual void Update(void) = 0;
	virtual void OnEvent(void *Event) = 0;
	virtual bool IsKeyPressed(Keys Key) = 0;
	virtual bool IsKeyReleased(Keys Key) = 0;
	virtual bool GetKeyState(Keys Key) = 0;
	virtual void GetMousePosition(int *x, int *y) = 0;
	virtual void GetMouseMotion(int *dx, int *dy) = 0;
	virtual bool IsMouseButtonPressed(MouseButtons Button) = 0;
};

#endif // IINPUT_H
