#include"MenuLayer.h"

enum {
	//菜单精灵tag
	Menu1Tag = 30,
	Menu2Tag = 31
};

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visiblesize = Director::getInstance()->getVisibleSize();

	auto resumeitem = MenuItemFont::create("resume", this, menu_selector(MenuLayer::resume));//resume(Ref* ref)中传入的参数为resumeitem
	auto restartitem = MenuItemFont::create("restart", this, menu_selector(MenuLayer::restart));
	auto exit = MenuItemFont::create("exit", this, menu_selector(MenuLayer::exit));
	auto menu1 = Menu::create(resumeitem, restartitem, exit, NULL);
	menu1->setPosition(Vec2(visiblesize.width / 2, visiblesize.height + menu1->getContentSize().height / 2));
	menu1->alignItemsVerticallyWithPadding(40);
	addChild(menu1,0,Menu1Tag);

	m_menuopen = MenuItemFont::create("Menu", this, menu_selector(MenuLayer::menuopen));
	m_menuopen->setVisible(true);
	m_menuopen->setEnabled(true);
	m_menuclose = MenuItemFont::create("Menu", this, menu_selector(MenuLayer::menuclose));
	m_menuclose->setVisible(false);
	m_menuclose->setEnabled(false);
	auto menu2 = Menu::create(m_menuopen, m_menuclose, NULL);
	menu2->setPosition(visiblesize*8/10);
	menu2->setScale(0.8f);
	addChild(menu2,0,Menu2Tag);

	return true;
}

MenuLayer* MenuLayer::create()
{
	auto pmenu = new MenuLayer;
	if (pmenu&&pmenu->init())
	{
		pmenu->autorelease();
		return pmenu;
	}
	else
	{
		delete pmenu;
		pmenu = nullptr;
		return nullptr;
	}
}

void MenuLayer::resume(Ref* ref)
{
	Director::getInstance()->resume();
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto menuitem = (MenuItem*)ref;
	auto menulayer = menuitem->getParent();
	auto move = MoveTo::create(1.0f, Vec2(visiblesize.width/2,visiblesize.height+menulayer->getContentSize().height/2));
	auto scale = ScaleTo::create(1.0f, 0.1f);
	auto spawn = Spawn::create(move, scale, NULL);
	menulayer->runAction(spawn);
}

void MenuLayer::restart(Ref* ref)
{

}
void MenuLayer::exit(Ref* ref)
{
	Director::getInstance()->end();
}

void MenuLayer::menuopen(Ref* ref)
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	m_menuopen->setVisible(false);
	m_menuopen->setEnabled(false);
	m_menuclose->setVisible(true);
	m_menuclose->setEnabled(true);

	auto menu1 = (Menu*)this->getChildByTag(Menu1Tag);
	auto move = MoveTo::create(1.0f, Vec2(visiblesize/2));
	auto scale = ScaleTo::create(1.0f, 1.0f);
	auto spawn = Spawn::create(move, scale, NULL);
	menu1->runAction(spawn);
}

void MenuLayer::menuclose(Ref* ref)
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	m_menuopen->setVisible(true);
	m_menuopen->setEnabled(true);
	m_menuclose->setVisible(false);
	m_menuclose->setEnabled(false);

	auto menu1 = (Menu*)this->getChildByTag(Menu1Tag);
	auto move = MoveTo::create(1.0f, Vec2(visiblesize.width / 2, visiblesize.height + menu1->getContentSize().height / 2));
	auto scale = ScaleTo::create(1.0f, 1.0f);
	auto spawn = Spawn::create(move, scale, NULL);
	menu1->runAction(spawn);
}