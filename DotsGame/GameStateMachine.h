#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

using namespace std;

#include <vector>
#include "State.h"

class Message;
class GameStateMachine //manages all gamestates
{
public:
	GameStateMachine();

	void pushState(State* pState); //add state without removing the previous state
	void changeState(State* pState); //remove current state and change adding another
	void popState(); //remove current state without adding another
	void broadcastMessage(Message* msg);
	void update(float deltaTime);
	void render();

protected:
private:

	vector<State*> m_gameStates;
};

#endif // GAMESTATEMACHINE_H
