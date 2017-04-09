#pragma once
#include"cocos2d.h"

USING_NS_CC;
class MenuLayer :public cocos2d::Layer
{
public:


	static MenuLayer* create();
	bool init();
	void resume(Ref*);
	void exit(Ref*);
	void restart(Ref*);

	void menuopen(Ref*);
	void menuclose(Ref*);

private:
	MenuItem* m_menuopen;
	MenuItem* m_menuclose;

};
