#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "cocos2d.h"
USING_NS_CC;
class backGround:public Layer
{
public:
	
	virtual bool init();
	CREATE_FUNC(backGround);
	void move();
private:
	Sprite* background1;
	Sprite* background2;
	float vy;
};
#endif
