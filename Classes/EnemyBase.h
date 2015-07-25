#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_
#include "cocos2d.h"
USING_NS_CC;
class EnemyBase :public Sprite
{
public:
	EnemyBase();
	~EnemyBase();
	virtual bool init();
	CREATE_FUNC(EnemyBase);

public:
	void initEnemy(const std::string& frameName,int &blowup);//初始化不同敌机，第一个为图片名字，第二个为爆炸动画帧数
	void move();
	void blowupAction();//爆炸动画
	void hurt(float dmg);//受伤动画
	bool getIsblowup();
private:
	std::string mFrameName;
	int blowupNums;//爆炸动画几张
	float vy;//敌机移动速度
	float hp;//敌机血量
	bool isBlowup;//是否爆炸
};
#endif
