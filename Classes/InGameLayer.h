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
	virtual void onEnterTransitionDidFinish();//��д�ú���
	virtual bool onTouchBegan(Touch* t, Event* e);//ע�ᴥ���¼�,��д����
	virtual void onTouchEnded(Touch* t, Event* e);//ע�ᴥ���¼�
	virtual void onTouchMoved(Touch* t, Event* e);
	void createBulletWithTimer(float dt);//�����ӵ�
	void createBonusWithTimer(float dt);//����������Ʒ
	void menuPauseCallback(Ref* r);
	static int getScore();//ȡ�÷���
	static int score;//��Ϸ����
	static int bulletState;//�ӵ�״̬ 0��Ĭ�� 1��˫���ӵ�
	static int bonus_counter;//��bonus�ļ���������¼��һ�����˼������������л���ͬbonus
private:
	backGround *nBackground;//��ӱ�����
	Player* mPlayer;//������
	void gameStep(float dt);//���ϵ���move����
	void gameStart();
	void addEvents();
	void createEnemyWithTimer(float dt);//schedule�ص�����
	void moveAllEnemy();//�ƶ��л�
	void moveAllBullet();//�ƶ��ӵ�
	void moveBonus();//�ƶ�bonus
	void eatBonus();//�Ե�bonus
	void allEnemyBoom();//���ел���ը
	
	void hitTestEnemyWithEnemy();//�ӵ��л���ײ���
	void hitTestPlayerWithEnemy();//�л��������ײ
	void gameOver();
	Point touchPos;
	Size size ;
	Vector<EnemyBase*> enemyList;//��ŵл�������
	Vector<Bullet*> bulletList;//�ӵ���������
	Vector<Bonus*> bonus;//������Ʒ����
	
	int score_fly;// ÿ�ܵл��ķ�����������������
	int bonus_time;//˫���ӵ�����ʱ��
	LabelTTF* label_score;//��ʾ�����Ŀؼ�
	LabelTTF* label_fly;
	Vector<LabelTTF*> vec_label;
	MenuItemImage* pause_menu;

	int game_time;//��Ϸ�����˶�õ�ʱ����������������Ʋ����ɻ�Ƶ�ʵĺ���
	void game_timeIncrease();
	void update(float dt);
	float getGameTime();

};
#endif
