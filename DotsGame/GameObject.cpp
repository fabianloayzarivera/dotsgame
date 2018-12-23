#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Vector2D position, int width, int height, string textureID, string soundID) 
{
	m_position = position;
	m_width = width;
	m_height = height;
	m_textureID = textureID;
	m_bDeleteMark = false;
	m_angle = 0.f;
	m_soundID = soundID;
}

void GameObject::draw()
{
	TextureManager::Instance()->draw(m_textureID, int(m_position.getX()), int(m_position.getY()), m_width,
		m_height, m_angle,DotsGame::Instance()->getRenderer());

}

void GameObject::playSound() const
{
	if (m_soundID.length() > 0)
		AudioManager::Instance()->playAudio(m_soundID);
	else
		cout << "No audio set" << endl;
}

void GameObject::clean()
{

}

GameObject::~GameObject() 
{
	this->clean();
}

Vector2D& GameObject::getPosition()
{
	return m_position;
}

int GameObject::getWidth()
{
	return m_width;
}

int GameObject::getHeight()
{
	return m_height;
}

void GameObject::setPosition(Vector2D position) 
{
	m_position = position;
}

void GameObject::setAngle(float angle)
{
	m_angle = angle;
}

float GameObject::getAngle() const 
{
	return m_angle;
}

void GameObject::setTextureId(string textureID)
{
	m_textureID = textureID;
}

const bool GameObject::isMarkedToDelete() const 
{
	return m_bDeleteMark;
}

void GameObject::setDeleteMark(bool mark) 
{
	m_bDeleteMark = mark;
}

