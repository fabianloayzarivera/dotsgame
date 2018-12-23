#include "Game.h"
#include "IntroState.h"
#include "InputHandler.h"
#include "Message.h"

Game* Game::s_pInstance = 0;

Game::Game()
{
	m_pRenderer = NULL;
	m_pWindow = NULL;
}

Game::~Game()
{
	this->clean();
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags)
{
	//try init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL initialize" << endl;
		//init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) // init window
		{
			cout << "SDL window initialize" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) //renderer init
			{
				cout << "Renderer initialized" << endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else {
				cout << "Render initilization error" << endl;
				return false;
			}
		}
		else {
			cout << "Window Initialization error" << endl;
			return false;
		}
	}
	else {
		cout << "SDL Initialization error" << endl;
		return false;
	}
	cout << "Initialization Success" << endl;
	m_running = true;

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		cout << "Failed to initialize TTF" << endl;
		return false;
	}
	//
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

	//init of GameStateMachine
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new IntroState(5.0f));

	//end
	return true;
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::update(float deltaTime)
{
	m_pGameStateMachine->update(deltaTime);
}

void Game::broadcastMessage(Message* msg)
{
	m_pGameStateMachine->broadcastMessage(msg);
}

void Game::handleEvents()
{
	InputHandler::Instance()->update();

}

void Game::quit()
{
	clean();
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

bool Game::running() const
{
	return m_running;
}

GameStateMachine* Game::getStateMachine()
{
	return m_pGameStateMachine;
}
