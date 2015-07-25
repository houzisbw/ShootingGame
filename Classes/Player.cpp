#include "Player.h"
#include "InGameLayer.h"
USING_NS_CC;
bool Player::init()
{
	bool bl = Sprite::init();
	//创建飞机
	initWithSpriteFrameName("hero_fly_1.png");
	flyAction();
	return bl;
}
void Player::moveTo(cocos2d::Point pos)
{
	this->setPosition(pos);
	Size size = Director::getInstance()->getVisibleSize();
	if (this->getPosition().x <= this->getContentSize().width / 2)
	{
		this->setPositionX(this->getContentSize().width / 2);
	}
	else if (this->getPosition().x >= size.width - this->getContentSize().width / 2)
	{
		this->setPositionX(size.width - this->getContentSize().width / 2);
	}


	if (this->getPositionY() <= this->getContentSize().height / 2)
	{
		this->setPositionY(this->getContentSize().height / 2);
	}
	else if (this->getPositionY() >= size.height - this->getContentSize().height / 2)
	{
		this->setPositionY(size.height - this->getContentSize().height / 2);
	}
}
void Player::flyAction()
{
	//容器里放2张动画纹理
	Vector<SpriteFrame*> actionList;
	SpriteFrame * frame_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_fly_1.png");
	SpriteFrame * frame_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_fly_2.png");
	actionList.pushBack(frame_1);
	actionList.pushBack(frame_2);

	Animation * mAnimation = Animation::createWithSpriteFrames(actionList, 0.3f);//动画帧创建
	Animate *mAnimate = Animate::create(mAnimation);//创建动画
	RepeatForever* loop = RepeatForever::create(mAnimate); 

	runAction(loop);

}
void  Player::blowupAction()
{
	
	
	
	Vector<SpriteFrame*> actionList;
	SpriteFrame * frame_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_1.png");
	SpriteFrame * frame_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_2.png");
	SpriteFrame * frame_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_3.png");
	SpriteFrame * frame_4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_4.png");
	actionList.pushBack(frame_1);
	actionList.pushBack(frame_2);
	actionList.pushBack(frame_3);
	actionList.pushBack(frame_4);
	Animation * mAnimation = Animation::createWithSpriteFrames(actionList, 0.3f);
	Animate *mAnimate = Animate::create(mAnimation);//创建动画
	//this->runAction(mAnimate);

	
	Sequence *seq = Sequence::create(mAnimate, NULL);
	this->runAction(seq);

	
	
	//回到初始点
	
	//Size size = Director::getInstance()->getVisibleSize();
	//this->setPosition(size.width / 2, size.height - 800);


}
Player::Player()
{
}


Player::~Player()
{
}
