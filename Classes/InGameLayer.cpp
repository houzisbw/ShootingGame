#include "InGameLayer.h"
#include "WelcomeLayer.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


USING_NS_CC;
bool InGameLayer::init()
{
	bool bl = Layer::create();
	size = Director::getInstance()->getVisibleSize();
	
	nBackground = backGround::create();
	addChild(nBackground);
	nBackground->setAnchorPoint(Point(0, 0));
	nBackground->setPosition(0, 0);
	mPlayer = Player::create();//CREATE_FUNC�Զ����øú�����init������ʼ��
	mPlayer->setPosition(size.width/2,size.height-800);
	addChild(mPlayer);

	pause_menu = MenuItemImage::create("pause_button.png", "resume_button.png", "pause_button.png", CC_CALLBACK_1(InGameLayer::menuPauseCallback, this));//ע���ʽ
	Menu * pm = Menu::create(pause_menu, NULL);
	addChild(pm,3);
	pm->setPosition(580, 900);
	
	score = 0;

	char s[20];
	sprintf(s, "%d", score);
	label_score = LabelTTF::create(s, "Arial-BoldMT", 60);
	label_score->setPosition(100, 900);
	label_score->setColor(Color3B(80,80,80));
	addChild(label_score,2);//Zorder ��Ϊ���÷�����ʾ�ڷɻ��Ϸ�
	
	//������� Ԥ����
	SimpleAudioEngine::getInstance()->preloadEffect("explosion.wav");//�л���ը
	SimpleAudioEngine::getInstance()->preloadEffect("explosion.mp3");//��ұ�ը
	SimpleAudioEngine::getInstance()->setEffectsVolume(1);




	
	return bl; 
}
void InGameLayer::onEnterTransitionDidFinish()//�����л������Զ����øú�����
{
	  gameStart();
	  addEvents();//��Ӵ����¼�

}
Scene* InGameLayer::createScene()
{
	Scene *scene = Scene::create();
	auto layer = InGameLayer::create();
	scene->addChild(layer);
	return scene;
}												
void InGameLayer::gameStart()
{
	srand(time(NULL));
	mPlayer->setPosition(size.width / 2, size.height - 800);
	mPlayer->setVisible(true);
	size = Director::getInstance()->getVisibleSize();
	this->schedule(SEL_SCHEDULE(&InGameLayer::gameStep), 0.02f);//ÿ��0.02�����gamestep����һ��	
	
	this->schedule(SEL_SCHEDULE(&InGameLayer::createBulletWithTimer), 0.2);//�����ӵ�
	this->schedule(SEL_SCHEDULE(&InGameLayer::createBonusWithTimer), 10);//����������Ʒ

	
	//ʱ�����Ӻ���,1�����һ��
	scheduleUpdate();
	
}
void InGameLayer::update(float dt)
{
	game_time++;
	if (game_time >= 3000)
	{
		game_time = 3000;
	}
	char s[20];
	sprintf(s, "%d", game_time);
	log(s);
}
float InGameLayer::getGameTime()
{
	if (game_time < 1000)
		return 0.5;
	else if (game_time >= 1000 && game_time < 2000)
		return 1;
	else
	{
		return 0.5;
	}
}
void InGameLayer::gameStep(float dt)
{
	nBackground->move();
	mPlayer->moveTo(touchPos);//��ҷɻ��ƶ�
	moveAllEnemy();//�ƶ����е���
	moveAllBullet();//�ƶ������ӵ�
	hitTestEnemyWithEnemy();//�ӵ���ײ���
	hitTestPlayerWithEnemy();//��ҵл����
	eatBonus();//�Ե�bonus
	moveBonus();//�ƶ�bonus
	//log("%d", enemyList.size());
	//log("%d", score);
	label_score->setString(StringUtils::format("%d", score));//��̬�ı����

	this->schedule(SEL_SCHEDULE(&InGameLayer::createEnemyWithTimer), 3.5 - game_time / 1000);//������ֵл�  ,Ƕ�׵���schedule�����ﵽ�ɻ�����Ƶ������Ŀ��
	
	
	
}
void InGameLayer::game_timeIncrease()
{
	game_time++;
}
void InGameLayer::moveAllBullet()
{
	Bullet* getBullet;
	for (int i = 0; i < bulletList.size(); i++)
	{
		getBullet = bulletList.at(i);
		getBullet->move();
		if (getBullet->getPositionY() >= 960 + 20)//���������Ƴ��ӵ�ָ��,2���Ƴ�
		{
			bulletList.eraseObject(getBullet);
		}
	}
}
void InGameLayer::moveAllEnemy()//����vector�����ел�Ȼ��ִ��move����
{
	EnemyBase* getEnemy;
	for (int i = 0; i < enemyList.size(); i++)
	{
		getEnemy = enemyList.at(i);
		getEnemy->move();
		if (getEnemy->getPositionY() <= 0)
		{
			enemyList.eraseObject(getEnemy);//������Ļ���޾��Ƴ��õл�
		}
	}
}
void InGameLayer::moveBonus()
{
	Bonus* bn;
	for (int i = 0; i < bonus.size(); i++)
	{
		bn = bonus.at(i);
		bn->bonusMove();
		if (bn->getPositionY() <= 0)
		{
			bonus.eraseObject(bn);
			bonus_counter++;//�ɳ���Ļ��bouns++����ʾ�Ѿ�������bonus����
		}
	}
}
void InGameLayer::eatBonus()
{
	Bonus* getBonus;
	for (int i = 0; i < bonus.size(); i++)
	{
		getBonus = bonus.at(i);
		if (getBonus->getBoundingBox().containsPoint(mPlayer->getPosition()))
		{
			bonus.eraseObject(getBonus);
			getBonus->removeFromParent();
			if (bonus_counter % 3 != 0)//�Ե�˫���ӵ�
			{
				bulletState = 1;//˫���ӵ��Ե�
				bonus_time = 100;
			}
			else//ը�����������зɻ� ,�����⣬���򱨴����
			{
				
				//allEnemyBoom();
			}
			//allEnemyBoom();
		}
	}
}
void  InGameLayer::allEnemyBoom()
{
	EnemyBase* getEnemy;
	for (int i = 0; i < enemyList.size(); i++)//Ϊ��ֻ��ը��һ���ֵл� ԭ����for������eraseobject����size��С
	{
		getEnemy = enemyList.at(i);
		getEnemy->blowupAction();		
		//enemyList.eraseObject(getEnemy);
		
	}
	for (int i = 0; i < enemyList.size(); i++)
	{
		getEnemy = enemyList.at(i);
		getEnemy->removeFromParent();
		enemyList.erase(i);
		
	}

}
bool InGameLayer::onTouchBegan(Touch* t, Event* e)//ע�ᴥ���¼�
{

	
	
	return true;
}
void InGameLayer::onTouchEnded(Touch* t, Event* e)
{

}
void InGameLayer::addEvents()
{
	EventListenerTouchOneByOne* touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(InGameLayer::onTouchBegan,this);
	touch->onTouchEnded = CC_CALLBACK_2(InGameLayer::onTouchEnded, this);
	touch->onTouchMoved = CC_CALLBACK_2(InGameLayer::onTouchMoved, this);

	//�¼�ע��
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(touch, this);
}
void InGameLayer::onTouchMoved(Touch* t, Event* e)
{
	touchPos = t->getLocation();

}
void InGameLayer::createBonusWithTimer(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();
	Bonus* b = Bonus::create();
	b->setPosition(CCRANDOM_0_1()*size.width, size.height+100);
	this->addChild(b,3);//����bonus��������һ��
	bonus.pushBack(b);//������������
}
void InGameLayer::createEnemyWithTimer(float dt)
{
	EnemyBase* mEnemy = EnemyBase::create();
	int enemyType = CCRANDOM_0_1() * 3 + 1;//�õ�1,2,3�����
	char enemyName[20];
	sprintf(enemyName, "enemy%d", enemyType);
	int blowupNums;
	if (enemyType == 1 || enemyType == 3)//��ը��������
		blowupNums = 4;
	else
		blowupNums = 7;
	mEnemy->initEnemy(enemyName, blowupNums);//��ʼ���л�
	
	
	//����ingamelayer����
	this->addChild(mEnemy,1);

	//�л���������,�������
	enemyList.pushBack(mEnemy);

	//mEnemy->blowupAction();
}
void InGameLayer::createBulletWithTimer(float dt)//�����ӵ�������,�ص�����
{
	if (bulletState == 0)
	{
		Bullet* mBullet = Bullet::create();
		mBullet->setPosition(mPlayer->getPosition() + Point(0, 100));//�ӵ��������
		this->addChild(mBullet);
		bulletList.pushBack(mBullet);
	}
	else if (bulletState == 1)//˫���ӵ�
	{
		Bullet* mBullet_1 = Bullet::create();
		Bullet* mBullet_2 = Bullet::create();
		mBullet_1->setPosition(mPlayer->getPosition() + Point(-20, 100));
		mBullet_2->setPosition(mPlayer->getPosition() + Point(20, 100));
		this->addChild(mBullet_1);
		this->addChild(mBullet_2);
		bulletList.pushBack(mBullet_1);
		bulletList.pushBack(mBullet_2);
		bonus_time--;//����ʱ�����
		if (bonus_time <= 0)
		{
			bulletState = 0;
			bonus_time = 0;
		}
	}

}
int InGameLayer::getScore()
{
	return score;
}
void InGameLayer::hitTestEnemyWithEnemy()//2��ѭ�����μ����ײ
{
	EnemyBase* getEnemy=NULL;
	Bullet*    getBullet=NULL;
	bool is = false;
	for (int i = enemyList.size()-1; i >=0; i--)//ɾ�� �õ������
	{
		
		getEnemy = enemyList.at(i);
		for (int j = bulletList.size() - 1; j >= 0; j--)
		{
					
			getBullet = bulletList.at(j);
			if (getBullet->hitTest(getEnemy))//�л���ָ��,����ӵ���л���ײ
			{
				getEnemy->hurt(1.0);//�л�����
				//ɾ���ӵ�
				getBullet->destory();
				bulletList.erase(j);
				if (getEnemy->getIsblowup())//����л����ݻ�,ɾ���л�
				{
					enemyList.erase(i);
					
					SimpleAudioEngine::getInstance()->playEffect("explosion.wav");
					
					//��Ϸ����++
					if (getEnemy->getTag() == 3)//��ɻ�
					{
						
						score_fly = 1000;
						score += 1000;
					}
					else if (getEnemy->getTag() == 2)
					{
						
						score_fly = 500;
						score += 500;
					}
					else
					{
						
						score_fly = 100;
						score += 100;
					}
					
					char s[20];
					is = true;
					sprintf(s, "%d", score_fly);
					label_fly = LabelTTF::create(s, "MarkerFelt-Thin", 60);	
					label_fly->setColor(Color3B(100, 100, 100));
					addChild(label_fly);

					vec_label.pushBack(label_fly);//����������ȥ

					label_fly->setPosition(getEnemy->getPosition());
					auto moveTo = MoveTo::create(1.0f,Point(100,900));					
									
					label_fly->runAction(moveTo);
				    
					
					break;//�������жϸõл���
				}
				
			}
		}
	}
	LabelTTF* l;//����÷��������У�������Ȼ����ʾ�ɹ�ȥ������
	for (int i = 0; i < vec_label.size(); i++)
	{
		l = vec_label.at(i);
		if (l->getPosition() == Point(100, 900))
		{
			
			//��Ϸ����++
			/*if (getEnemy->getTag() == 3)//��ɻ�
			{
				score += 1000;
				
			}
			else if (getEnemy->getTag() == 2)
			{
				score += 500;
				
			}
			else
			{
				score += 100;
				
			}*/
			auto s2= ScaleBy::create(0.1f, 1.5);
			auto seq = Sequence::create(s2,s2->reverse(),NULL);//null������������������
			//label_score->runAction(seq);  //�����⣬�����᲻��������ôȥ����������
			//score += score_fly;

			l->removeFromParent();
			vec_label.eraseObject(l);
		}
	}


}
void InGameLayer::hitTestPlayerWithEnemy()
{
	EnemyBase * getEnemy;
	for (int i = 0; i < enemyList.size()-1; i++)
	{

		getEnemy = enemyList.at(i);
		if (getEnemy->getBoundingBox().containsPoint(mPlayer->getPosition()))
		{
			
			SimpleAudioEngine::getInstance()->playEffect("explosion.mp3");
			this->unschedule(SEL_SCHEDULE(&InGameLayer::createBulletWithTimer));//ֹͣ�����ӵ�
			auto action1 = CallFunc::create([=](){
			
				mPlayer->blowupAction();// �տ�ʼִ���˵�һ֡����������ִ���˸ú����ˣ������
				//Ϊ�˷�ֹ�ɻ���ը������ƶ��ɻ�
				EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
				dispatcher->removeEventListenersForTarget(this);//����removealllistener���������г�����listener���Ƴ��ˣ������Ƴ��ò���¼�������
			
			});
			
			auto action2 = CallFunc::create([=](){
			
				mPlayer->setVisible(false);
				gameOver();
			
			});

			auto action3 = CallFunc::create([=](){

				
				/*Size size = Director::getInstance()->getVisibleSize();
				auto score_layer = LayerColor::create(Color4B(200, 200, 200, 255));
				score_layer->setContentSize(Size(size.width / 2, size.height / 2));
				score_layer->setPosition(size.width / 4, size.height / 4);
				score_layer->setAnchorPoint(Point(0.5,0.5));
				addChild(score_layer,3);*/

			
			});
			ActionInterval * delaytime = CCDelayTime::create(2);//��ʱ����,Ŀ����Ϊ���ñ�ը����ִ�����

			Sequence *seq = Sequence::create(action1,delaytime,action2 ,NULL);
			this->runAction(seq);
			
												
		}
	}
}
void InGameLayer::gameOver()
{
    //�Ƴ������¼���������Ƴ����򱨴�,��Ϊ
	
	
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5, GameOver::createScene()));

}
void InGameLayer::menuPauseCallback(Ref* r)
{
	if (!Director::getInstance()->isPaused())//���������ͣ
	{
		//pause_menu->setNormalSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause.png"));
		//pause_menu->setNormalSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_hl.png"));
		Director::getInstance()->pause();
	}
	else
	{
		//pause_menu->setNormalSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause.png"));
		//pause_menu->setNormalSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_hl.png"));
		Director::getInstance()->resume();
	}
}
int InGameLayer::bulletState = 0;
int InGameLayer::score=0;
int InGameLayer::bonus_counter = 1;
InGameLayer::InGameLayer() :
touchPos(320, 160),
game_time(0)
{
}


InGameLayer::~InGameLayer()
{
}
