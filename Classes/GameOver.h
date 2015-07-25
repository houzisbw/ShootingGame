#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_ 
#include "cocos2d.h"
class GameOver:public cocos2d::Layer
{
public:
	GameOver();
	~GameOver();
	virtual bool init();
	CREATE_FUNC(GameOver);
	static cocos2d::Scene* createScene();
	void replaceScene(Ref* r);
	
	int getHighestScore();
	static int highestScore;
};
#endif
