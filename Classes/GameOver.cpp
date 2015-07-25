#include "GameOver.h"
#include "InGameLayer.h"
#include "WelcomeLayer.h"
USING_NS_CC;
bool GameOver::init()
{
	
	highestScore = UserDefault::getInstance()->getIntegerForKey("highestScore");//必须在这里写这句话，否则static初始化把这个score变成0
	
	if (InGameLayer::score > GameOver::highestScore)
	{
		UserDefault::getInstance()->setIntegerForKey("highestScore", InGameLayer::score);
		UserDefault::getInstance()->flush();
		GameOver::highestScore = InGameLayer::score;
	}

	
	Size size = Director::getInstance()->getVisibleSize();
	Layer::init();
	auto lc = LayerColor::create(Color4B(200, 200, 200, 255));
	addChild(lc);
	lc->setContentSize(Size(size.width,size.height ));
	char s[20];
	sprintf(s, "Your Score: %d", InGameLayer::getScore());//将ingamelayer的score设为static，则可以在文件间传递参数
	LabelTTF *lt = LabelTTF::create(s, "Courier", 40);
	lt->setPosition(size.width / 2, size.height / 2);
	addChild(lt);

	//菜单
	auto mt = MenuItemFont::create("Continue", CC_CALLBACK_1(GameOver::replaceScene, this));
	mt->setFontName("Courier");
	mt->setFontSize(40);
	auto m = Menu::create(mt, NULL);
	addChild(m);
	m->setPosition(size.width / 2, size.height / 2 - 80);

	//历史最好成绩
	
	char p[20];
	sprintf(p, "HIGHEST  %d",highestScore );
	auto hs = LabelTTF::create(p, "Courier", 40);
	addChild(hs);
	hs->setPosition(size.width / 2, size.height * 3 / 4);

	

	return true;
}
int GameOver::highestScore=0;//static必须初始化
void GameOver::replaceScene(Ref* r)
{
	Director::getInstance()->replaceScene(WelcomeLayer::createScene());
}

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();//创建layer
	scene->addChild(layer);
	return scene;
}

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}
