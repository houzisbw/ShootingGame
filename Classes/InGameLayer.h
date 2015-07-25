#ifndef _INGAMELAYER_H_
#define _INGAMELAYER_H_
#include "cocos2d.h"
#include "backGround.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Bullet.h"
#include "Bonus.h"
USING_NS_CC;
class InGameLayer:public Layer
{
public:
	InGameLayer();
	~InGameLayer();
	virtual bool init();
	CREATE_FUNC(InGameLayer);
	static Scene* createScene();
	virtual void onEnterTransitionDidFinish();//重写该函数
	virtual bool onTouchBegan(Touch* t, Event* e);//注册触摸事件,重写函数
	virtual void onTouchEnded(Touch* t, Event* e);//注册触摸事件
	virtual void onTouchMoved(Touch* t, Event* e);
	void createBulletWithTimer(float dt);//创建子弹
	void createBonusWithTimer(float dt);//创建奖励物品
	void menuPauseCallback(Ref* r);
	static int getScore();//取得分数
	static int score;//游戏分数
	static int bulletState;//子弹状态 0：默认 1：双发子弹
	static int bonus_counter;//吃bonus的计数器，记录下一共吃了几个，作用是切换不同bonus
private:
	backGround *nBackground;//添加背景层
	Player* mPlayer;//添加玩家
	void gameStep(float dt);//不断调用move函数
	void gameStart();
	void addEvents();
	void createEnemyWithTimer(float dt);//schedule回调函数
	void moveAllEnemy();//移动敌机
	void moveAllBullet();//移动子弹
	void moveBonus();//移动bonus
	void eatBonus();//吃到bonus
	void allEnemyBoom();//所有敌机爆炸
	
	void hitTestEnemyWithEnemy();//子弹敌机碰撞检测
	void hitTestPlayerWithEnemy();//敌机与玩家碰撞
	void gameOver();
	Point touchPos;
	Size size ;
	Vector<EnemyBase*> enemyList;//存放敌机的容器
	Vector<Bullet*> bulletList;//子弹数组容器
	Vector<Bonus*> bonus;//奖励物品容器
	
	int score_fly;// 每架敌机的分数，用来做动画的
	int bonus_time;//双发子弹持续时间
	LabelTTF* label_score;//显示分数的控件
	LabelTTF* label_fly;
	Vector<LabelTTF*> vec_label;
	MenuItemImage* pause_menu;

	int game_time;//游戏进行了多久的时间计数器，用来控制产生飞机频率的函数
	void game_timeIncrease();
	void update(float dt);
	float getGameTime();

};
#endif
