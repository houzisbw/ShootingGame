#include "backGround.h"
USING_NS_CC;
bool backGround::init()
{
	bool bl = Layer::create();
	vy = 5.5;
	background1 = Sprite::createWithSpriteFrameName("background_2.png");
	addChild(background1);
	background1->setAnchorPoint(Point(0, 0));
	background1->setPosition(0,0);

	background2 = Sprite::createWithSpriteFrameName("background_2.png");
	addChild(background2);
	background2->setAnchorPoint(Point(0, 0));
	background2->setPosition(0, background1->getPositionY()+background1->getContentSize().height-2);//防止出现黑线


	
	return bl;
}
void backGround::move()//每一次调用向下移动,循环滚动,2张图连接处有黑线
{
	float nextPos1 = background1->getPositionY() - vy;
	float nextPos2 = background2->getPositionY() - vy;
	background1->setPositionY(nextPos1);
	background2->setPositionY(nextPos2);

	if (nextPos1 < -background1->getContentSize().height)
	{
		nextPos1 = background2->getPositionY() + background2->getContentSize().height-1;
		background1->setPositionY(nextPos1);
	}
	else if (nextPos2 < -background2->getContentSize().height)
	{
		nextPos2 = background1->getPositionY() + background1->getContentSize().height-1;
		background2->setPositionY(nextPos2);
	}
}


