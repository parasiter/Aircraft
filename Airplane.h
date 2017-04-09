#pragma once
#include"Bullet.h"

USING_NS_CC;

class Airplane : public cocos2d::Sprite
{
public:
	static Airplane* create(const std::string&,unsigned);
	bool init(const std::string&, unsigned);

private:
	Bullet* bullet;
	unsigned HP;
};

