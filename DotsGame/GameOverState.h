#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

using namespace std;

#include <string>
#include "State.h"
#include <vector>

class Message;
class GameObject;
class GameOverState : public State
{
public:
	GameOverState(const float &delay, const int &score, const int &maxScore);
	~GameOverState() {}
	virtual void update(float deltaTime);
	virtual void render();
	virtual void receiveMessage(Message* msg);
	virtual bool onEnterState();
	virtual bool onExitState();

	virtual string getStateID() const;
private:
	float m_delay;
	int					m_finalScore;
	int					m_maxScore;
	static const string s_gameOverID;
	vector<GameObject*> m_gameObjects;
	void playGame() const;
};

#endif // GAMEOVERSTATE_H

