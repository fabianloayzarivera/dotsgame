#include "IntroState.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "InputHandler.h"
#include "GameState.h"
#include "Game.h"
#include "Message.h"
#include "Dot.h"
#include <iostream>


using namespace std;

const string IntroState::s_introID = "INTRO";
float timeElapsed = 0.f;
IntroState::IntroState(const float &delay)
:m_delay(delay)
{
	
}

string IntroState::getStateID() const
{
	return s_introID;
}

void IntroState::update(float deltaTime)
{
	
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update(deltaTime);
	}
	timeElapsed += deltaTime;
	if (timeElapsed >= this->m_delay)
		playGame();

}

void IntroState::render()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	//Draw Background
	TextureManager::Instance()->draw("introbackground", 0, 0, 720,800, 0, DotsGame::Instance()->getRenderer());
	//Draw Text
	TextureManager::Instance()->drawText("Fabian Loayza Presents:", 100, 200, DotsGame::Instance()->getRenderer(), { 218,165,32, 255});
	TextureManager::Instance()->drawText("THE  DOT  GAME", 170, 400, DotsGame::Instance()->getRenderer(), { 128,0,0, 255});

}

bool IntroState::onEnterState()
{
	TextureManager::Instance()->loadFont("fontFile.TTF", 100);
	if (!TextureManager::Instance()->load("IntroBackground.png", "introbackground", DotsGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!AudioManager::Instance()->loadMusic("backgroundMusic.wav"))
	{
		return false;
	}

	AudioManager::Instance()->playMusic();
	cout << "entering IntroState" << endl;
	return true;
}

bool IntroState::onExitState()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("greendot"); 
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	TextureManager::Instance()->clearFromTextureMap("introbackground");
	TextureManager::Instance()->clearFont();
	cout << "exiting IntroState" << endl;
	return true;
}

void IntroState::playGame() const 
{
	DotsGame::Instance()->getStateMachine()->changeState(new GameState());
}

void IntroState::receiveMessage(Message* msg) 
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->receiveMessage(msg);
	}
}
