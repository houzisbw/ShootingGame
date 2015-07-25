#include "Bonus.h"
#include "InGameLayer.h"
USING_NS_CC;

bool Bonus::init()
{
	Sprite::init();
	if (InGameLayer::bonus_counter % 3 != 0)
	{
		initWithFile("bullet_add.png");//�����������resource����ļ���ʼ��bonus������plist�ļ�
	}
	else
	{
		initWithFile("bomb_icon.png");
	}


	return true;
}
void Bonus::bonusMove()
{
	this->setPositionY(this->getPositionY() - vy);
	if (this->getPositionY() <= 0)
	{
		this->removeFromParent();
	}
}
Bonus::Bonus():
vy(10)
{
}


Bonus::~Bonus()
{
}
