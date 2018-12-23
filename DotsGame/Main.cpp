#include <iostream>
#include <string>
#include "Game.h"

using namespace std;


int main(int argc, char * argv[])
{


	if (DotsGame::Instance()->init("DotsGame", 100, 100, 720, 800, 0))
	{
		float lastFrame = (float)SDL_GetTicks() * 0.001f;

		while (DotsGame::Instance()->running())
		{
			
			float currentFrame = (float)SDL_GetTicks() * 0.001f;
			float deltaTime = currentFrame - lastFrame;

			DotsGame::Instance()->handleEvents();
			DotsGame::Instance()->update(deltaTime);
			DotsGame::Instance()->render();

			lastFrame = currentFrame;
			SDL_Delay(1);
		
		}
		DotsGame::Instance()->clean();
	}

	return 0;
}