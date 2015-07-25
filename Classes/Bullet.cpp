#include "Bullet.h"
#include "InGameLayer.h"
bool Bullet::init()
{
	bool bl = Sprite::init();
	if (InGameLayer::bulletState == 0)//state判断创建怎么样的子弹
	{
		initWithSpriteFrameName("bullet1_.png");
	}
	else if (InGameLayer::bulletState==1)
	{
		initWithFile("bullet_1.png");
	}

	
	return bl;
}
void Bullet::move()
{
	this->setPositionY(this->getPositionY() + vy);
	Size size = Director::getInstance()->getVisibleSize();

	if (this->getPositionY() >= size.height + this->getContentSize().height / 2)
	{
		destory();//移除飞出屏幕的子弹
	}
}
bool Bullet::hitTest(Node* enemy)//碰撞检测函数
{
	return enemy->getBoundingBox().containsPoint(this->getPosition());
	//如果敌机包含子弹这个点，则返回true
}

void Bullet::destory()
{
	this->removeFromParent();
}
Bullet::Bullet() :vy(30)
{
}


Bullet::~Bullet()
{
}
