#ifndef _BULLET_H_
#define _BULLET_H_
#include "cocos2d.h"
USING_NS_CC;
class Bullet:public Sprite
{
public:
	Bullet();
	~Bullet();
	virtual bool init();
	CREATE_FUNC(Bullet);
public:
	void move();
	bool hitTest(Node* enemy);//Åö×²¼ì²âº¯Êý
	void destory();
private:
	float vy;


};

#endif