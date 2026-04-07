#pragma once
#include "Object.h"
class Character : public Object
{
public:
	Character();
	~Character();
	virtual void Attack() {}
	virtual void Move() {}
	void SetVel(Vector2D vel) { Velocity = vel; }
	Vector2D GetVel() { return Velocity; }	
protected:
	unsigned int Hp;
	Vector2D Velocity;
	unsigned int State;
public:
	int GetHp() { return Hp; }
	void SetHp(int hp) { Hp = hp; }
	void DownHp(int dhp) { Hp -= dhp; }
};