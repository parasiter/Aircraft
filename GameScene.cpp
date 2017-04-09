#include"GameScene.h"
#include"Bullet.h"
#include"Airplane.h"
#include"random"

enum Zorder
{
	BackgroundLayerZorder = 1,
	ActionLayerZorder = 2,
	MenuLayerZorder = 3
};
enum Tag
{
	BackgroundLayerTag = 1,
	ActionLayerTag = 2,
	MenuLayerTag = 3,
	//背景精灵tag
	BackgroundTag = 10,
	
	//动作精灵tag
	BulletTag = 20,
	AirplaneTag = 21,
	EnemyTag =22,

	//菜单精灵tag
	MenuTag = 30,
	StartTag = 31,
	HighScoreTag = 32,
	ExitTag = 33,

	//动作tag
	ActionTag = 40
};

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();

	//设置背景层
	Layer* l_background = Layer::create();
	Sprite* s_background = Sprite::create("AirplaneResource/ui/shoot_background/background.png");
	s_background->setPosition(size / 2);
	auto s_size = s_background->getContentSize();
	s_background->setScale(size.height / s_size.height);
	l_background->addChild(s_background, 0, BackgroundTag);
	this->addChild(l_background, BackgroundLayerZorder, BackgroundLayerTag);

	//设置动作层
	Layer* l_action = Layer::create();
	Airplane* airplane = Airplane::create("AirplaneResource/ui/shoot/hero1.png", 10);
	airplane->setPosition(size.width / 2, airplane->getContentSize().height / 2);
	l_action->addChild(airplane, 0, AirplaneTag);
	addChild(l_action, ActionLayerZorder, ActionLayerTag);
	schedule(schedule_selector(GameScene::shoot), 0.1f);//自动射击

	schedule(schedule_selector(GameScene::createnemy), 5.0f);
	
	//设置菜单层
	auto menulayer = MenuLayer::create();
	addChild(menulayer, MenuLayerZorder, MenuLayerTag);



	//监控键盘
	auto listenerkeypad = EventListenerKeyboard::create();
	listenerkeypad->onKeyPressed = CC_CALLBACK_2(GameScene::onkeypressed, this);
	listenerkeypad->onKeyReleased = CC_CALLBACK_2(GameScene::onkeyreleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeypad, this);
	return true;
}

GameScene* GameScene::create()
{
	GameScene* gamescene = new GameScene;
	if (gamescene&&gamescene->init())
	{
		gamescene->autorelease();
		return gamescene;
	}
	delete gamescene;
	gamescene = nullptr;
	return nullptr;
}


void GameScene::onkeypressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	Action* move;
	Director::getInstance()->setProjection(Director::Projection::_2D);
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		move = MoveBy::create(2.0f, Vec2(0, 500));
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		move = MoveBy::create(2.0f, Vec2(0, -500));
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		move = MoveBy::create(2.0f, Vec2(-500, 0));
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		move = MoveBy::create(2.0f, Vec2(500, 0));
		break;
	}
	}
	getChildByTag(ActionLayerTag)->getChildByTag(AirplaneTag)->runAction(move);
	move->setTag(ActionTag);
}

void GameScene::onkeyreleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	getChildByTag(ActionLayerTag)->getChildByTag(AirplaneTag)->stopActionByTag(ActionTag);
}

void GameScene::shoot(float dt)
{
	auto bullet = Bullet::create("AirplaneResource/ui/shoot/bullet1.png", 10);
	auto move = MoveBy::create(2.0f, Vec2(0, 1000));
	auto end = CCCallFuncN::create(this, callfuncN_selector(GameScene::moveActionEnd));
	bullet->runAction(Sequence::create( move, end, NULL));
	auto airplane = (Airplane*)getChildByTag(ActionLayerTag)->getChildByTag(AirplaneTag);
	bullet->setPosition(airplane->getPosition().x,airplane->getPosition().y+airplane->getContentSize().height/2);
	getChildByTag(ActionLayerTag)->addChild(bullet,0,BulletTag);
}

void GameScene::createnemy(float dt)
{
	auto size = Director::getInstance()->getVisibleSize();
	auto enemy = Airplane::create("AirplaneResource/ui/shoot/enemy1.png", 5);
	static std::uniform_int_distribution<unsigned> u(0, 10);
	static std::default_random_engine e;
	enemy->setPosition(u(e) * 100 % (unsigned)size.width, size.height + 100);
	auto move1 = MoveTo::create(2.0f, Vec2(size.width/u(e), size.height - u(e)*40));
	auto delay = DelayTime::create(1.0f);
	auto move2 = MoveTo::create(8.0f, Vec2(u(e) * 100 % (unsigned)size.width, -100));
	enemy->runAction(Sequence::create(move1, delay, move2, NULL));
	getChildByTag(ActionLayerTag)->addChild(enemy, 0);
	v_enemy.push_back(enemy);
}

void GameScene::moveActionEnd(Node* ref)
{
	auto sp = (Sprite*)ref;
	sp->removeFromParent();
}