#include "EnemyBase.h"
USING_NS_CC;
bool EnemyBase::init()
{
	bool bl = Sprite::init();

	return bl;
}
void EnemyBase::initEnemy(const std::string& frameName, int &blowup)
{
	mFrameName = frameName;
	blowupNums = blowup;
	vy = CCRANDOM_0_1() * 5 + 5;//初始化敌机速度
	int temp = (frameName.at(5)-'0');//at函数取得某一个字符
	if (temp == 2)//大飞机
	{
		hp = (temp ) * 5;  //10hp
		this->setTag(3);
	}
	else if (temp == 3)//中飞机
	{
		hp = (temp) * 2;  //6hp
		this->setTag(2);
	}
	else //小飞机
	{
		hp = (temp)/2; //1hp
		this->setTag(1);
	}

	std::string key = frameName + "_fly_1.png";
	initWithSpriteFrameName(key);

	float w = this->getContentSize().width;
	float h = this->getContentSize().height;
	
	Size size = Director::getInstance()->getVisibleSize();

	
	
	this->setPosition(CCRANDOM_0_1()*(size.width-w)+w/2,size.height+h);

}
void EnemyBase::move()
{
	this->setPositionY(this->getPositionY() - vy);
	if (this->getPositionY() <= 0)
	{
		this->removeFromParent();
		
	}
}
void EnemyBase::blowupAction()//爆炸动画
{
	isBlowup = true;
	char keyBack[20];
	Vector<SpriteFrame*> actionList;
	SpriteFrame *frame;
	for (int i = 1; i <= blowupNums; i++)
	{

		sprintf(keyBack, "_blowup_%d.png", i);
		std::string key = mFrameName + keyBack;
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(key);
		actionList.pushBack(frame);

	}
	Animation* mAnimation = Animation::createWithSpriteFrames(actionList, 0.1f);
	Animate * mAnimate = Animate::create(mAnimation);
	RemoveSelf* remove = RemoveSelf::create();//移除自己,不是fromparent

	Sequence *seq = Sequence::create(mAnimate,remove,NULL);
	
	
	this->runAction(seq);


}
void EnemyBase::hurt(float dmg)//受伤动画
{
	hp -= dmg;
	if (hp <= 0)
		blowupAction();
}
bool  EnemyBase::getIsblowup()
{
	return isBlowup;
}
EnemyBase::EnemyBase() :isBlowup(false)//开始未爆炸
{
}


EnemyBase::~EnemyBase()
{
}
