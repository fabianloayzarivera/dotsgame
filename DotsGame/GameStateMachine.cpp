#include "GameStateMachine.h"
#include <iostream>
#include "Message.h"

using namespace std;

GameStateMachine::GameStateMachine()
{
	//...
}

void GameStateMachine::pushState(State *pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnterState();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExitState())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(State *pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			//do nothing, the last state it's the same as the new one
		}
		if (m_gameStates.back()->onExitState())
		{
			m_gameStates.pop_back();
		}
	}
	//push back new state
	m_gameStates.push_back(pState);

	//initialize it
	m_gameStates.back()->onEnterState();

}

void GameStateMachine::update(float deltaTime)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update(deltaTime);
	}
}

void GameStateMachine::broadcastMessage(Message* msg)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->receiveMessage(msg);
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}
