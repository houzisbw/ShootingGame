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
	void moveTo(cocos2d::Point pos);//�ƶ���ĳһ��
	void blowupAction();
private:
	void flyAction();//���ж���
	//�ɻ��ݻٶ���


};

#endif