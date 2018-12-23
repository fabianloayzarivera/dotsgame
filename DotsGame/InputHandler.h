#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Vector2D.h"

using namespace std;

enum MOUSE_BUTTONS
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:

	static InputHandler* Instance() 
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance; 
	}

	void update();
	void clean(); 

	bool		getMouseButtonState(int buttonNumber); 
	Vector2D*	getMousePosition(); 
	bool		isKeyDown(SDL_Scancode key);

private:

	vector< vector<bool> >		m_buttonStates; 
	vector<bool>				m_mouseButtonStates; 
	Vector2D*					m_mousePosition; 
	const Uint8*				m_keystates;
	static InputHandler*		s_pInstance;
	InputHandler(); 
	~InputHandler(); 
	void						onKeyDown();
	void						onKeyUp();
	void						onMouseMove(SDL_Event& event);
	void						onMouseButtonDown(SDL_Event& event);
	void						onMouseButtonUp(SDL_Event& event);

};

#endif // INPUTHANDLER_H
