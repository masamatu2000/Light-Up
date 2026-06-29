#pragma once
#include "Enemy.h"
class Creeper :
    public Enemy
{
public:
	Creeper(const Vector2D& pos);
	~Creeper();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

