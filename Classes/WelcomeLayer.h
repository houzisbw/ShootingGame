#ifndef _WELCOME_LAYER_H_
#define _WELCOME_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;
class WelcomeLayer:public Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	void logoAction();
	static Scene* createScene();
	void startGame(Ref * r);
	bool isSaveFile();
	int getHighestScore();
	
	
	
};

#endif