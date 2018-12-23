#ifndef  DOT_H
#define	 DOT_H

using namespace std;

#include "GameObject.h"
enum DOT_TYPE { GREEN, RED };
class Message;

class Dot : public GameObject 
{
public:
	static Dot* createDot(Vector2D position, int width, int height, DOT_TYPE type, float lifeTime, bool persistent = false, string soundID="");
	Dot(Vector2D position, int width, int height, string textureID, DOT_TYPE type, float lifeTime, bool persistent = false, string soundID = "");
	~Dot() {};
	void			clicked(DOT_TYPE click);
	void			update(float deltaTime) override;
	void			receiveMessage(Message* msg) override;
private:
	float			m_lifeTime;
	const DOT_TYPE  m_type;
	bool			m_bPersistent;
};


#endif // DOT_H
