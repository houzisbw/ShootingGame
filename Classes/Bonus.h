#ifndef _BONUS_H_
#define _BONUS_H_
#include "cocos2d.h"
class Bonus:public cocos2d::Sprite
{
public:
	Bonus();
	~Bonus();
	virtual bool init();
	CREATE_FUNC(Bonus);
public:
	void bonusMove();
private:
	float vy;//½±ÀøÏÂÂäËÙ¶È
};
#endif
