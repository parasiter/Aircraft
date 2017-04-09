#include"StartScene.h"
#include"GameScene.h"

USING_NS_CC;

enum Zorder
{
	BackgroundLayerZorder = 0,
	ActionLayerZorder = 1,
	MenuLayerZorder = 2
};
enum Tag 
{
	BackgroundLayerTag = 1,
	ActionLayerTag = 2,
	MenuLayerTag =3,

	BackgroundTag = 10,

	StartTag =31,
	HighScoreTag =32,
	ExitTag =33,

};



bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();
	Layer* l_background = Layer::create();
	Sprite* s_background = Sprite::create("AirplaneResource/ui/shoot_background/background.png");
	s_background->setPosition(size/2);
	auto s_size = s_background->getContentSize();
	s_background->setScale(size.height / s_size.height);

	l_background->addChild(s_background, 0, BackgroundTag);
	this->addChild(l_background, BackgroundLayerZorder, BackgroundLayerTag);

	MenuItem* start = MenuItemFont::create("Start", this, menu_selector(StartScene::start));
	MenuItem* highscore = MenuItemFont::create("HighScore", this, menu_selector(StartScene::highscore));
	MenuItem* exit = MenuItemFont::create("Exit", this, menu_selector(StartScene::exit));
	auto menu = Menu::create(start, highscore, exit, NULL);
	menu->alignItemsVerticallyWithPadding(100);
	this->addChild(menu, MenuLayerZorder, MenuLayerTag);

	return true;
}

StartScene* StartScene::create()
{
	auto startscene = new StartScene;
	if (startscene && startscene->init())
	{
		startscene->autorelease();
		return startscene;
	}
	delete startscene;
	startscene = nullptr;
	return nullptr;
}

void StartScene::start(Ref* ref)
{
	Director::getInstance()->purgeCachedData();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,GameScene::create()));
}

void StartScene::highscore(Ref* ref)
{
	auto highscore = HighScore::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, highscore));
}

void StartScene::exit(Ref* ref)
{
	Director::getInstance()->end();
}

bool HighScore::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getWinSize();

	auto s_background = Sprite::create("AirplaneResource/ui/shoot_background/background.png");
	s_background->setPosition(Vec2(size / 2));
	this->addChild(s_background, 0);

	auto back = MenuItemFont::create("back", this, menu_selector(HighScore::back));
	auto menu = Menu::create(back, NULL);
	menu->alignItemsVerticallyWithPadding(100);
	this->addChild(menu, 1);

	return true;
}

void HighScore::back(Ref* ref)
{
	auto director = Director::getInstance();
	director->replaceScene(TransitionFade::create(1.0f, StartScene::create()));
}

HighScore* HighScore::create()
{
	auto highscore = new HighScore;
	if (highscore&&highscore->init())
	{
		highscore->autorelease();
		return highscore;
	}
	delete highscore;
	highscore = nullptr;
	return nullptr;
}