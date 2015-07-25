#include "GameOver.h"
#include "InGameLayer.h"
#include "WelcomeLayer.h"
USING_NS_CC;
bool GameOver::init()
{
	
	highestScore = UserDefault::getInstance()->getIntegerForKey("highestScore");//����������д��仰������static��ʼ�������score���0
	
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
	sprintf(s, "Your Score: %d", InGameLayer::getScore());//��ingamelayer��score��Ϊstatic����������ļ��䴫�ݲ���
	LabelTTF *lt = LabelTTF::create(s, "Courier", 40);
	lt->setPosition(size.width / 2, size.height / 2);
	addChild(lt);

	//�˵�
	auto mt = MenuItemFont::create("Continue", CC_CALLBACK_1(GameOver::replaceScene, this));
	mt->setFontName("Courier");
	mt->setFontSize(40);
	auto m = Menu::create(mt, NULL);
	addChild(m);
	m->setPosition(size.width / 2, size.height / 2 - 80);

	//��ʷ��óɼ�
	
	char p[20];
	sprintf(p, "HIGHEST  %d",highestScore );
	auto hs = LabelTTF::create(p, "Courier", 40);
	addChild(hs);
	hs->setPosition(size.width / 2, size.height * 3 / 4);

	

	return true;
}
int GameOver::highestScore=0;//static�����ʼ��
void GameOver::replaceScene(Ref* r)
{
	Director::getInstance()->replaceScene(WelcomeLayer::createScene());
}

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();//����layer
	scene->addChild(layer);
	return scene;
}

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}
