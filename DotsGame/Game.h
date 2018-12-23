#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "GameStateMachine.h"


using namespace std;

class Message;
class Game
{
public:

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags); //conjunt de coses que configurar al iniciar el programa
	void render(); 
	void update(float deltaTime);
	void handleEvents();
	void broadcastMessage(Message* msg);
	void clean();
	void quit();

	//GETs
	bool running() const;
	GameStateMachine* getStateMachine();


private:
	Game();
	static Game*		s_pInstance;
	bool				m_running; 
	SDL_Window*			m_pWindow; 
	SDL_Renderer*		m_pRenderer; 
	GameStateMachine*	m_pGameStateMachine;

};

typedef Game DotsGame;
#endif // GAME_H
