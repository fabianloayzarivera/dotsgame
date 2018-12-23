#include "Dot.h"
#include "Game.h"
#include "Message.h"
#include "AudioManager.h"
#include "GameOverState.h"

Dot* Dot::createDot(Vector2D position, int width, int height, DOT_TYPE type, float lifeTime, bool persistent, string soundID)
{
	Dot* newDot = nullptr;
	switch (type)
	{
	case GREEN:
		newDot = new Dot(position, width, height, "greendot", type, lifeTime, persistent, soundID);

		break;
	case RED:
		newDot = new Dot(position, width, height, "reddot", type, lifeTime, persistent, soundID);
		break;
	default:
		break;
	}
	return newDot;
}

Dot::Dot(Vector2D position, int width, int height, string textureID, DOT_TYPE type, float lifeTime, bool persistent, string soundID)
	:GameObject(position, width, height, textureID, soundID),
	m_type(type)
{
	m_bPersistent = persistent;
	m_lifeTime = lifeTime;
}

void Dot::update(float deltaTime)
{
	if (!m_bPersistent)
	{
		m_lifeTime -= deltaTime;
		if (m_lifeTime <= 0)
			this->setDeleteMark(true);
	}
	else 
	{
		this->setAngle(this->getAngle() + 180.0f * deltaTime);
	}
}

void Dot::clicked(DOT_TYPE click) 
{
	if (m_type == click)
	{
		//cout << "SCORE!" << endl;
		this->setDeleteMark(true);
		MessageScore msg(m_type);
		this->playSound();
		DotsGame::Instance()->broadcastMessage(&msg);

	}
	else
	{
		//cout << "GAME OVER!" << endl;
		MessageGameOver msg("You pressed the wrong button!");
		DotsGame::Instance()->broadcastMessage(&msg);
	}
}

void Dot::receiveMessage(Message* msg)
{
}
