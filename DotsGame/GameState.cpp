#include "GameState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Vector2D.h"
#include "GameOverState.h"
#include "AudioManager.h"
#include "Game.h"
#include "Message.h"
#include "Tile.h"
#include "Dot.h"
#include <iostream>


using namespace std;

const string GameState::s_gameID = "GAME";
const unsigned int	ROWS = 10;
const unsigned int	COLUMNS = 10;
const unsigned int	TILE_WIDTH = 64;
const unsigned int	TILE_HEIGHT = 64;
const unsigned int	SCORE_TO_WIN= 10;
const float			DOT_SPAWN_DELAY = 2.0f;
const float			DOT_LIFE = 2.0f;

float spawnCooldown;

GameState::GameState()
{
	m_scorePosition = Vector2D(40.0f, 40.0f);
}

string GameState::getStateID() const
{
	return s_gameID;
}

void GameState::update(float deltaTime)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update(deltaTime);
	}

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ) //We deallocate all dots that are marked to kill
	{
		if ((*it)->isMarkedToDelete())
		{
			delete(*it);															
			it = m_gameObjects.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = m_scoreDots.begin(); it != m_scoreDots.end(); ++it) //New Dots created during update functions
	{
		m_gameObjects.push_back(*it);
	}
	m_scoreDots.clear();
	
	spawnCooldown -= deltaTime;
	if (spawnCooldown <= 0)
	{
		int maxRand = m_grid.size();
		int randNum = rand() % maxRand;
		Tile* randTile = m_grid.at(randNum);
		int randType = rand() % 100;
		Dot* dot;
		if(randType > 50)
			dot = Dot::createDot(randTile->getPosition(), 64, 64, GREEN, DOT_LIFE, false, "pickgreensound");
		else
			dot = Dot::createDot(randTile->getPosition(), 64, 64, RED, DOT_LIFE, false, "pickredsound");

		if (dot)
		{
			randTile->setTileDot(dot);
			m_gameObjects.push_back(dot);
		}
		spawnCooldown = DOT_SPAWN_DELAY;
	}
	
}

void GameState::render()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameState::onEnterState()
{
	if (!TextureManager::Instance()->load("GreenGem.png", "greendot", DotsGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("RedGem.png", "reddot", DotsGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("TileRock.png", "tile", DotsGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("TileRockOver.png", "tilehover", DotsGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!AudioManager::Instance()->loadAudio("pickgreensound.wav", "pickgreensound"))
	{
		return false;
	}
	if (!AudioManager::Instance()->loadAudio("pickredsound.wav", "pickredsound"))
	{
		return false;
	}
	
	Vector2D tilePosition(Vector2D(40.0f, 120.0f));
	for (int i = 0; i < ROWS; i++) 
	{
		for (int j = 0; j < COLUMNS; j++) 
		{
			Tile* newTile = new Tile(tilePosition, TILE_WIDTH, TILE_HEIGHT, "tile");
			m_grid.push_back(newTile);
			m_gameObjects.push_back(newTile);
			tilePosition.setX(tilePosition.getX() + TILE_WIDTH);
		}
		tilePosition.setY(tilePosition.getY() + TILE_HEIGHT);
		tilePosition.setX(40.0f);
	}

	spawnCooldown = DOT_SPAWN_DELAY;
	m_score = 0;
	cout << "entering GameState" << endl;
	return true;
}

bool GameState::onExitState()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("greendot");
	TextureManager::Instance()->clearFromTextureMap("reddot");
	TextureManager::Instance()->clearFromTextureMap("tile");
	TextureManager::Instance()->clearFromTextureMap("tilehover");
	cout << "exiting GameState" << endl;
	return true;
}

void GameState::receiveMessage(Message* msg)
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->receiveMessage(msg);
	}

	MessageScore* msgScore = dynamic_cast<MessageScore*>(msg);
	if (msgScore)
	{
		Dot* scoreDot = Dot::createDot(m_scorePosition, TILE_WIDTH, TILE_HEIGHT, msgScore->type, 0.0f, true);
		m_scorePosition.setX(m_scorePosition.getX() + TILE_WIDTH);
		m_scoreDots.push_back(scoreDot);
		m_score++;
		if (m_score == SCORE_TO_WIN)
		{
			DotsGame::Instance()->getStateMachine()->changeState(new GameOverState(5.0f, m_score, COLUMNS));
		}
	}

	MessageGameOver* msgGameOver = dynamic_cast<MessageGameOver*>(msg);
	if (msgGameOver)
	{
		DotsGame::Instance()->getStateMachine()->changeState(new GameOverState(5.0f, m_score, COLUMNS));
	}
}

GameState::~GameState() 
{
	
}