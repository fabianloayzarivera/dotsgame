#ifndef INTROSTATE_H
#define INTROSTATE_H

using namespace std;

#include <string>
#include "State.h"
#include <vector>

class Message;
class GameObject;
class IntroState : public State
{
public:
	IntroState(const float &delay);
	~IntroState() {}
	virtual void update(float deltaTime);
	virtual void render();
	virtual void receiveMessage(Message* msg);
	virtual bool onEnterState();
	virtual bool onExitState();

	virtual string getStateID() const;
private:
	const float m_delay;
	static const string s_introID;
	vector<GameObject*> m_gameObjects;
	void playGame() const;

};

#endif // INTROSTATE_H
