#pragma once
#include "Enemy.h"
class Berserker :
    public Enemy
{
public:
	Berserker(const Vector2D& pos);
	~Berserker();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

