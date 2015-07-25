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
	mPlayer = Player::create();//CREATE_FUNC自动调用该函数和init函数初始化
	mPlayer->setPosition(size.width/2,size.height-800);
	addChild(mPlayer);

	pause_menu = MenuItemImage::create("pause_button.png", "resume_button.png", "pause_button.png", CC_CALLBACK_1(InGameLayer::menuPauseCallback, this));//注意格式
	Menu * pm = Menu::create(pause_menu, NULL);
	addChild(pm,3);
	pm->setPosition(580, 900);
	
	score = 0;

	char s[20];
	sprintf(s, "%d", score);
	label_score = LabelTTF::create(s, "Arial-BoldMT", 60);
	label_score->setPosition(100, 900);
	label_score->setColor(Color3B(80,80,80));
	addChild(label_score,2);//Zorder 是为了让分数显示在飞机上方
	
	//添加音乐 预加载
	SimpleAudioEngine::getInstance()->preloadEffect("explosion.wav");//敌机爆炸
	SimpleAudioEngine::getInstance()->preloadEffect("explosion.mp3");//玩家爆炸
	SimpleAudioEngine::getInstance()->setEffectsVolume(1);




	
	return bl; 
}
void InGameLayer::onEnterTransitionDidFinish()//场景切换完了自动调用该函数，
{
	  gameStart();
	  addEvents();//添加触摸事件

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
	this->schedule(SEL_SCHEDULE(&InGameLayer::gameStep), 0.02f);//每隔0.02秒调用gamestep函数一次	
	
	this->schedule(SEL_SCHEDULE(&InGameLayer::createBulletWithTimer), 0.2);//生产子弹
	this->schedule(SEL_SCHEDULE(&InGameLayer::createBonusWithTimer), 10);//生产奖励物品

	
	//时间增加函数,1秒调用一次
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
	mPlayer->moveTo(touchPos);//玩家飞机移动
	moveAllEnemy();//移动所有敌人
	moveAllBullet();//移动所有子弹
	hitTestEnemyWithEnemy();//子弹碰撞检测
	hitTestPlayerWithEnemy();//玩家敌机检测
	eatBonus();//吃到bonus
	moveBonus();//移动bonus
	//log("%d", enemyList.size());
	//log("%d", score);
	label_score->setString(StringUtils::format("%d", score));//动态改变分数

	this->schedule(SEL_SCHEDULE(&InGameLayer::createEnemyWithTimer), 3.5 - game_time / 1000);//随机出现敌机  ,嵌套调用schedule函数达到飞机出现频率增大目的
	
	
	
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
		if (getBullet->getPositionY() >= 960 + 20)//从容器中移除子弹指针,2次移除
		{
			bulletList.eraseObject(getBullet);
		}
	}
}
void InGameLayer::moveAllEnemy()//遍历vector中所有敌机然后执行move函数
{
	EnemyBase* getEnemy;
	for (int i = 0; i < enemyList.size(); i++)
	{
		getEnemy = enemyList.at(i);
		getEnemy->move();
		if (getEnemy->getPositionY() <= 0)
		{
			enemyList.eraseObject(getEnemy);//超出屏幕界限就移除该敌机
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
			bonus_counter++;//飞出屏幕后bouns++，表示已经出现了bonus个数
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
			if (bonus_counter % 3 != 0)//吃到双发子弹
			{
				bulletState = 1;//双发子弹吃到
				bonus_time = 100;
			}
			else//炸弹，消除所有飞机 ,有问题，程序报错崩溃
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
	for (int i = 0; i < enemyList.size(); i++)//为何只爆炸了一部分敌机 原因：在for里用了eraseobject导致size变小
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
bool InGameLayer::onTouchBegan(Touch* t, Event* e)//注册触摸事件
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

	//事件注册
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
	this->addChild(b,3);//保持bonus在最上面一层
	bonus.pushBack(b);//加入容器数组
}
void InGameLayer::createEnemyWithTimer(float dt)
{
	EnemyBase* mEnemy = EnemyBase::create();
	int enemyType = CCRANDOM_0_1() * 3 + 1;//得到1,2,3随机数
	char enemyName[20];
	sprintf(enemyName, "enemy%d", enemyType);
	int blowupNums;
	if (enemyType == 1 || enemyType == 3)//爆炸动画张数
		blowupNums = 4;
	else
		blowupNums = 7;
	mEnemy->initEnemy(enemyName, blowupNums);//初始化敌机
	
	
	//加入ingamelayer层中
	this->addChild(mEnemy,1);

	//敌机容器放入,方便管理
	enemyList.pushBack(mEnemy);

	//mEnemy->blowupAction();
}
void InGameLayer::createBulletWithTimer(float dt)//加入子弹数组中,回调函数
{
	if (bulletState == 0)
	{
		Bullet* mBullet = Bullet::create();
		mBullet->setPosition(mPlayer->getPosition() + Point(0, 100));//子弹跟随玩家
		this->addChild(mBullet);
		bulletList.pushBack(mBullet);
	}
	else if (bulletState == 1)//双发子弹
	{
		Bullet* mBullet_1 = Bullet::create();
		Bullet* mBullet_2 = Bullet::create();
		mBullet_1->setPosition(mPlayer->getPosition() + Point(-20, 100));
		mBullet_2->setPosition(mPlayer->getPosition() + Point(20, 100));
		this->addChild(mBullet_1);
		this->addChild(mBullet_2);
		bulletList.pushBack(mBullet_1);
		bulletList.pushBack(mBullet_2);
		bonus_time--;//持续时间减少
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
void InGameLayer::hitTestEnemyWithEnemy()//2重循环依次检测碰撞
{
	EnemyBase* getEnemy=NULL;
	Bullet*    getBullet=NULL;
	bool is = false;
	for (int i = enemyList.size()-1; i >=0; i--)//删除 用倒序遍历
	{
		
		getEnemy = enemyList.at(i);
		for (int j = bulletList.size() - 1; j >= 0; j--)
		{
					
			getBullet = bulletList.at(j);
			if (getBullet->hitTest(getEnemy))//敌机是指针,如果子弹与敌机碰撞
			{
				getEnemy->hurt(1.0);//敌机受伤
				//删除子弹
				getBullet->destory();
				bulletList.erase(j);
				if (getEnemy->getIsblowup())//如果敌机被摧毁,删除敌机
				{
					enemyList.erase(i);
					
					SimpleAudioEngine::getInstance()->playEffect("explosion.wav");
					
					//游戏分数++
					if (getEnemy->getTag() == 3)//大飞机
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

					vec_label.pushBack(label_fly);//放入数组中去

					label_fly->setPosition(getEnemy->getPosition());
					auto moveTo = MoveTo::create(1.0f,Point(100,900));					
									
					label_fly->runAction(moveTo);
				    
					
					break;//不用再判断该敌机了
				}
				
			}
		}
	}
	LabelTTF* l;//必须得放入数组中，否则仍然会显示飞过去的数字
	for (int i = 0; i < vec_label.size(); i++)
	{
		l = vec_label.at(i);
		if (l->getPosition() == Point(100, 900))
		{
			
			//游戏分数++
			/*if (getEnemy->getTag() == 3)//大飞机
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
			auto seq = Sequence::create(s2,s2->reverse(),NULL);//null不能忘，否则程序崩溃
			//label_score->runAction(seq);  //有问题，分数会不断增大，怎么去解决这个问题
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
			this->unschedule(SEL_SCHEDULE(&InGameLayer::createBulletWithTimer));//停止产生子弹
			auto action1 = CallFunc::create([=](){
			
				mPlayer->blowupAction();// 刚开始执行了第一帧动画，就算执行了该函数了，不会等
				//为了防止飞机爆炸后可以移动飞机
				EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
				dispatcher->removeEventListenersForTarget(this);//不能removealllistener，否则所有场景的listener被移除了，必须移除该层的事件监听器
			
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
			ActionInterval * delaytime = CCDelayTime::create(2);//延时动作,目的是为了让爆炸动画执行完毕

			Sequence *seq = Sequence::create(action1,delaytime,action2 ,NULL);
			this->runAction(seq);
			
												
		}
	}
}
void InGameLayer::gameOver()
{
    //移除侦听事件，如果不移除，则报错,因为
	
	
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5, GameOver::createScene()));

}
void InGameLayer::menuPauseCallback(Ref* r)
{
	if (!Director::getInstance()->isPaused())//如果不是暂停
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
