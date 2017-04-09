#include"Bullet.h"

Bullet* Bullet::create(const std::string &s, unsigned i)
{
	auto pbullet = new Bullet;
	if (pbullet&&pbullet->init(s,i))
	{
		pbullet->autorelease();
		return pbullet;
	}
	else
	{
		delete pbullet;
		pbullet = nullptr;
		return nullptr;
	}
}

bool Bullet::init(const std::string& s, unsigned i)
{
	if (!Sprite::initWithFile(s))
	{
		return false;
	}
	filename = s;
	power = i;
	return true;
}
