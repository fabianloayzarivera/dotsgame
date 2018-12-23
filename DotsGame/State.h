#ifndef STATE_H
#define STATE_H

using namespace std;

#include <string>
class Message;
class State
{
public:
	State();
	virtual		~State();
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void receiveMessage(Message* msg) = 0;
	virtual bool onEnterState() = 0; 
	virtual bool onExitState() = 0; 

	virtual string getStateID() const = 0;
};

#endif // STATE_H