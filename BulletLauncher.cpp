#include"BulletLauncher.h"

BulletLauncher* BulletLauncher::create(Bullet* bullet)
{
	BulletLauncher* bulletlauncher = new BulletLauncher;
	if (bulletlauncher&&bulletlauncher->init(bullet))
	{
		bulletlauncher->autorelease();
		return bulletlauncher;
	}
	else
	{
		delete bulletlauncher;
		bulletlauncher = nullptr;
		return nullptr;
	}
}

bool BulletLauncher::init(Bullet* bu)
{
	if (!Node::init())
	{
		return false;
	}
	bullet = bu;
	schedule(schedule_selector(BulletLauncher::shoot),0.5f);
	return true;
}

void BulletLauncher::shoot(float dt)
{
	Bullet* bu = Bullet::create(bullet->filename,bullet->power);
	bu->setPosition(0,0);
	addChild(bu);
	bu->runAction(MoveBy::create(10.0f, Vec2(0, 1000)));
}

