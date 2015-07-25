#include "WelcomeLayer.h"
#include "InGameLayer.h"
#include "GameOver.h"
USING_NS_CC;
bool WelcomeLayer::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	
	bool bl = Layer::init();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameArts-hd.plist");
	Sprite *bg = Sprite::createWithSpriteFrameName("background_2.png");
	bg->setAnchorPoint(Point(0,0));
	addChild(bg);
    
	logoAction();

	/*auto label = LabelTTF::create("123", "", 60);
	label->setPosition(400, 400);
	auto s2 = MoveBy::create(0.2f, Point(100,100));
	auto seq = Sequence::create(s2, s2->reverse(),NULL);
	label->runAction(seq);
	addChild(label);*/
	
	
	

	
	
	return bl;
}
bool WelcomeLayer::isSaveFile()
{
	if (!UserDefault::getInstance()->getBoolForKey("score"))
	{
		UserDefault::getInstance()->setBoolForKey("score", true);
		UserDefault::getInstance()->setIntegerForKey("highestScore", 0);
		UserDefault::getInstance()->flush();
		return false;
	}
	else
		return true;
}	
int  WelcomeLayer::getHighestScore()
{


	if (isSaveFile())
	{
		GameOver::highestScore = UserDefault::getInstance()->getIntegerForKey("highestScore");
		return GameOver::highestScore;

	}
	else
		return 0;

}
void WelcomeLayer::startGame(Ref * r)
{
	Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, InGameLayer::createScene()));
}
void WelcomeLayer::logoAction()
{
	Size size = Director::getInstance()->getVisibleSize();
	
	auto logo = Sprite::create("logo.png");
	addChild(logo);
	logo->setOpacity(0);//默认不显示
	logo->setPosition(size.width/2,size.height/2+150);

	FadeIn *fi = FadeIn::create(2);//逐渐显示,必须用不同action，才能用于2个不同的物体
	FadeIn *fj = FadeIn::create(2);
	

	auto start_menu = MenuItemImage::create("resume_button.png", "resume_button.png", CC_CALLBACK_1(WelcomeLayer::startGame, this));
	Menu *menu = Menu::create(start_menu, NULL);
	addChild(menu);
	menu->setPosition(size.width / 2, size.height / 2 - 100);
	menu->setOpacity(0);
	
	logo->runAction(fi);
	menu->runAction(fj);
	//auto st = ScaleBy::create(0.5f, 2);	
	//auto s = Sequence::create(st, st->reverse());
	//auto r = RepeatForever::create(s);
	//menu->runAction(st);//菜单不能缩放
}
Scene* WelcomeLayer::createScene()//创建一个场景
{
	Scene *sc = Scene::create();
	WelcomeLayer * ly = WelcomeLayer::create();
	sc->addChild(ly);
	return sc;
}
WelcomeLayer::WelcomeLayer()
{
}


WelcomeLayer::~WelcomeLayer()
{
}
