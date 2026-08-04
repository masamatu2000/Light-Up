#pragma once
#include "Enemy.h"

class Poison :
    public Enemy
{
public:
	Poison(const Vector2D& pos);
	~Poison();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

