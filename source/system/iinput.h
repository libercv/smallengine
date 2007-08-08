
#ifndef IINPUT_H
#define IINPUT_H

// Enumeración de las teclas que puede usar el motor
// Seguramente esto vaya en otro archivo de cabecera
// Algo asi como inputenums.h
enum Keys {KeyDown=0, KeyUp, KeyRight, KeyLeft, KeyEscape, KeySpace, KeyReturn, KeyPause, KeyEnd, KeyHome, MAX_KEYS};
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
