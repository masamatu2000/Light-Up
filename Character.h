#pragma once
#include "Object.h"
class Character : public Object
{
public:
	Character();
	~Character();
	virtual void Attack();
protected:
	unsigned int Hp;
	Vector2D Velocity;
	unsigned int State;
};