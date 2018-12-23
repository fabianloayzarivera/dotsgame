#include "Tile.h"
#include "Game.h"
#include "Dot.h"
#include "Message.h"
#include "InputHandler.h"

Tile::Tile(Vector2D position, int width, int height, string textureID)
	:GameObject(position, width, height, textureID)
{
	tileDot = nullptr;
	m_bReleasedLeft = false;
	m_bReleasedRight = false;
}

void Tile::update(float deltaTime)
{
	const Vector2D* mousePosition = InputHandler::Instance()->getMousePosition();
	if (checkMouseOver(mousePosition))
	{
		this->setTextureId("tilehover");
		if (!checkMouseClickLeft(mousePosition))
			checkMouseClickRight(mousePosition);
	}
	else
		this->setTextureId("tile");

	if (tileDot)
	{
		if (tileDot->isMarkedToDelete())
			tileDot = nullptr;
	}
}

const bool Tile::checkMouseOver(const Vector2D* mousePosition) 
{
	
	if (mousePosition->getX() >= this->getPosition().getX() &&        // right of the left edge AND
		mousePosition->getX() <= this->getPosition().getX() + this->getWidth() &&   // left of the right edge AND
		mousePosition->getY() >= this->getPosition().getY() &&        // below the top AND
		mousePosition->getY() <= this->getPosition().getY() + this->getHeight()) {   // above the bottom
		return true;
	}
	return false;
}

const bool Tile::checkMouseClickLeft(const Vector2D* mousePosition) 
{
	if (InputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleasedLeft)
	{
		//cout << "Clicked Left!" << endl;
		if (tileDot)
			tileDot->clicked(GREEN);
		m_bReleasedLeft = false;
		return true;
	}
	else if (!InputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_bReleasedLeft = true;
		return false;
	}
	return false;
}

const bool Tile::checkMouseClickRight(const Vector2D* mousePosition)
{
	if (InputHandler::Instance()->getMouseButtonState(RIGHT) && m_bReleasedRight)
	{
		//cout << "Clicked Right!" << endl;
		if (tileDot)
			tileDot->clicked(RED);
		m_bReleasedRight = false;
		return true;
	}
	else if (!InputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		m_bReleasedRight = true;
		return false;
	}
	return false;
}

void Tile::setTileDot(Dot* dot) 
{
	tileDot = dot;
}

void Tile::receiveMessage(Message* msg)
{
}
Tile::~Tile() 
{
	tileDot = nullptr;
}