#ifndef  MESSAGE_H
#define	 MESSAGE_H
#include <string>

enum DOT_TYPE;
class Message 
{
	//...
	virtual void LogMessage()=0;
};

class MessageScore :public Message 
{
public:
	MessageScore(DOT_TYPE aType) : type(aType) {}
	DOT_TYPE type; 
	void LogMessage() { cout << "Log: ScoreMessage" << endl; }
};

class MessageGameOver : public Message 
{
public:
	MessageGameOver(string aReason) : reason(aReason){}
	string reason;
	void LogMessage() { cout << "Log: GameOverMessage" << endl; }
};

#endif 