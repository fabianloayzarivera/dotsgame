#include "GameOverState.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "GameState.h"
#include "Game.h"
#include "Message.h"
#include <iostream>


using namespace std;

const string GameOverState::s_gameOverID = "GAMEOVER";

GameOverState::GameOverState(const float &delay, const int& score, const int &maxScore)
{
	m_delay = delay;
	m_finalScore = score;
	m_maxScore = maxScore;
}

string GameOverState::getStateID() const
{
	return s_gameOverID;
}

void GameOverState::update(float deltaTime)
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update(deltaTime);
	}
	m_delay -= deltaTime;
	if (m_delay <= 0.0f)
		playGame();
}

void GameOverState::render()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	//Draw Background
	TextureManager::Instance()->draw("gameoverbackground", 0, 0, 720, 800, 0, DotsGame::Instance()->getRenderer());
	//Draw Text
	if(m_finalScore != m_maxScore)
		TextureManager::Instance()->drawText("Game Over", 400, 400, DotsGame::Instance()->getRenderer(), { 218,165,32, 255 });
	else
		TextureManager::Instance()->drawText("You Win", 400, 400, DotsGame::Instance()->getRenderer(), { 218,165,32, 255 });
	TextureManager::Instance()->drawText("Score:", 470, 500, DotsGame::Instance()->getRenderer(), { 128,0,0, 255 });
	string scoreText = to_string(m_finalScore) + "/" + to_string(m_maxScore);
	TextureManager::Instance()->drawText(scoreText.c_str(), 470, 600, DotsGame::Instance()->getRenderer(), { 218,165,32, 255 });
}

bool GameOverState::onEnterState()
{
	TextureManager::Instance()->loadFont("fontFile.TTF", 100);
	if (!TextureManager::Instance()->load("GameOverBackground.png", "gameoverbackground", DotsGame::Instance()->getRenderer()))
	{
		return false;
	}	
	cout << "entering GameOverState" << endl;
	return true;
}

bool GameOverState::onExitState()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	cout << "exiting GameOverState" << endl;
	return true;
}

void GameOverState::receiveMessage(Message* msg) 
{

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->receiveMessage(msg);
	}
}

void GameOverState::playGame() const
{
	DotsGame::Instance()->getStateMachine()->changeState(new GameState());
}