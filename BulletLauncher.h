#pragma once
#include"cocos2d.h"
#include"Bullet.h"
#include"vector"

USING_NS_CC;

class BulletLauncher : public cocos2d::Node
{
public:
	static BulletLauncher* create(Bullet*);
	bool init(Bullet*);
	void shoot(float dt);
private:
	Bullet* bullet;
};

