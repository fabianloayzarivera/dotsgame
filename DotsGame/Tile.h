#ifndef  TILE_H
#define	 TILE_H

using namespace std;

#include "GameObject.h"

class Dot;
class Message;

class Tile : public GameObject
{
public:
	Tile(Vector2D position, int width, int height, string textureID);
	~Tile();
	void clean() { tileDot = nullptr; }
	void update(float deltaTime) override;
	void receiveMessage(Message* msg) override;
	void setTileDot(Dot* dot);
private:
	Dot*		tileDot;
	bool		m_bReleasedLeft;
	bool		m_bReleasedRight;
	const bool	checkMouseOver(const Vector2D* mousePosition);
	const bool	checkMouseClickLeft(const Vector2D* mousePosition);
	const bool	checkMouseClickRight(const Vector2D* mousePosition);
};

#endif // TILE_H