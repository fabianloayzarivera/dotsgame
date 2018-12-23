#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;

#include <string>
#include "State.h"
#include "Vector2D.h"
#include <vector>

class Message;
class GameObject;
class Tile;
class Dot;
class GameState : public State
{
public:
	GameState();
	~GameState();
	virtual void update(float deltaTime);
	virtual void render();
	virtual void receiveMessage(Message* msg);
	virtual bool onEnterState();
	virtual bool onExitState();

	virtual string getStateID() const;
private:
	vector<Tile*> m_grid;
	vector<Dot*>  m_scoreDots;
	unsigned int		m_score;
	static const string s_gameID;
	vector<GameObject*> m_gameObjects;
	Vector2D			m_scorePosition;
};

#endif // GAMESTATE_H

