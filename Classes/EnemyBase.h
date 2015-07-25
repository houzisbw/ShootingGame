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
	void initEnemy(const std::string& frameName,int &blowup);//��ʼ����ͬ�л�����һ��ΪͼƬ���֣��ڶ���Ϊ��ը����֡��
	void move();
	void blowupAction();//��ը����
	void hurt(float dmg);//���˶���
	bool getIsblowup();
private:
	std::string mFrameName;
	int blowupNums;//��ը��������
	float vy;//�л��ƶ��ٶ�
	float hp;//�л�Ѫ��
	bool isBlowup;//�Ƿ�ը
};
#endif
