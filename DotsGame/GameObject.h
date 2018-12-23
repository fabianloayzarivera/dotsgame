#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "TextureManager.h"
#include "AudioManager.h"
#include "Vector2D.h"

class Message;
class GameObject
{
public:
	GameObject(Vector2D position, int width, int height, string textureID, string soundID = "");
	virtual				~GameObject();
	void				draw();
	virtual void		clean();
	virtual void		update(float deltaTime) = 0;
	virtual void		receiveMessage(Message* msg) = 0;
	Vector2D&			getPosition();
	float				getAngle() const;
	int					getWidth();
	int					getHeight();
	void				setPosition(Vector2D position);
	void				setAngle(float angle);
	void				setTextureId(string textureID);
	const bool			isMarkedToDelete() const ;
	void				playSound() const;
	void				setDeleteMark(bool mark);
protected:

	Vector2D			m_position; 
	float				m_angle;
	int					m_width;
	int					m_height;
	string				m_textureID;
	string				m_soundID;
	bool				m_bDeleteMark;
};


#endif // GAMEOBJECT_H
