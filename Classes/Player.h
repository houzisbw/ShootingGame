#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cocos2d.h"
class Player:public cocos2d::Sprite
{
public:
	Player();
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);
public:
	void moveTo(cocos2d::Point pos);//移动到某一点
	void blowupAction();
private:
	void flyAction();//飞行动画
	//飞机摧毁动画


};

#endif