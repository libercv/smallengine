#ifndef INPUT_H
#define INPUT_H

#include <windows.h>
#include <windowsx.h>

#include "iinput.h" 

#include "window.h" 

namespace Small
{
	class Input : public IInput
	{
	private:
		// Mapa que relaciona una VKEY con una tecla de funcion de Small
		unsigned char KeyMap[256];

		// Mapa de teclas que indica si una tecla está pulsada o no
		bool KeyState[MAX_KEYS];

		// Mapa de teclas que indica si la tecla ha sido presionada en este frame
		bool KeyPressed[MAX_KEYS];

		// Mapa de teclas que indica si la tecla ha sido soltada en este frame
		bool KeyReleased[MAX_KEYS];

		// Posición del ratón.
		unsigned short x,y;
			
		// Desplazamiento del ratón desde el frame anterior.
		signed short dx,dy;

		Input(void);
		~Input(void) {};
		Input(Input const&) {};
		Input &operator=(Input const&) {};

		void OnKeyPressed(WPARAM key, bool pressed);
		void ResetBuffers(void);

	public:
		static Input &Instance()
		{
			static Input oInput;
			return oInput;
		}

		void Update(void);


		void OnEvent(void *Event) {};

		/*
		{
			MSG *msg;

			msg = (MSG *)Event;

			switch( msg->message )
			{
				case WM_KEYDOWN:
					OnKeyPressed(msg->wParam,true);
					break;

				case WM_KEYUP:
					OnKeyPressed(msg->wParam,false);
					break;
			}
		};
		*/

		inline bool IsKeyPressed(Keys Key)
		{
			return KeyPressed[Key];
		};

		inline bool IsKeyReleased(Keys Key)
		{
			return KeyReleased[Key];
		};

		inline bool GetKeyState(Keys Key)
		{
			return KeyState[Key];
		};

		inline bool IsMouseButtonPressed(MouseButtons Button)
		{
			// PENDIENTE: devolver el estado de los botones de raton
			return false;
		};

		void GetMousePosition(int *outX, int *outY)
		{
			// PENDIENTE: ahora mismo (x,y) no se actualiza. Se tienen que ir actualizando a partir de
			// (dx,dy) en Update (restringir las coordenadas de raton a las dimensiones de la ventana)
			*outX = x;
			*outY = y;
		};

		void GetMouseMotion(int *outDx, int *outDy)
		{
			*outDx = dx;
			*outDy = dy;
		};
	};
} // namespace Small

#endif // INPUT_H