#pragma once
#include"cocos2d.h"
#include"Bullet.h"
#include"MenuLayer.h"
#include"Airplane.h"
#include"vector"

USING_NS_CC;

class GameScene : public Scene
{
public:

	static GameScene* create();
	bool init();
	void onkeypressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void onkeyreleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void shoot(float dt);

	void createnemy(float dt);

	void moveActionEnd(Node*);//callfuncNֻ����node*������������ref

private:
	std::vector<Bullet*> v_bullet;
	std::vector<Airplane*> v_enemy;
};

