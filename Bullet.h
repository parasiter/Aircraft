#pragma once
#include"cocos2d.h"
#include"vector"

USING_NS_CC;
class Bullet : public cocos2d::Sprite
{
public:
	static Bullet* create(const std::string&, unsigned);
	virtual bool init(const std::string&,unsigned);
	unsigned power;
	std::string filename;
};