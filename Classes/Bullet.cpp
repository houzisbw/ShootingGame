#include "Bullet.h"
#include "InGameLayer.h"
bool Bullet::init()
{
	bool bl = Sprite::init();
	if (InGameLayer::bulletState == 0)//state�жϴ�����ô�����ӵ�
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
		destory();//�Ƴ��ɳ���Ļ���ӵ�
	}
}
bool Bullet::hitTest(Node* enemy)//��ײ��⺯��
{
	return enemy->getBoundingBox().containsPoint(this->getPosition());
	//����л������ӵ�����㣬�򷵻�true
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
