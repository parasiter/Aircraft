#pragma once
#include"cocos2d.h"

USING_NS_CC;

class StartScene :public cocos2d::Scene
{
public:
	bool init();
	static StartScene* create();
	void start(Ref*);
	void highscore(Ref*);
	void exit(Ref*);

private:

};


class HighScore :public cocos2d::Scene
{
public:
	bool init();
	static HighScore* create();
	void back(Ref* ref);

private:

};

