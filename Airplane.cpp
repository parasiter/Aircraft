#include"Airplane.h"

Airplane* Airplane::create(const std::string& filename, unsigned hp)
{
	auto airplane = new Airplane;
	if (airplane&&airplane->init(filename,hp))
	{
		airplane->autorelease();
		return airplane;
	}
	else
	{
		delete airplane;
		airplane = nullptr;
		return nullptr;
	}
}

bool Airplane::init(const std::string& filename, unsigned hp)
{
	if (!Sprite::initWithFile(filename))
		return false;
	HP = hp;
	return true;
}


