#pragma once
#include "Enemy.h"
class Debuffer :
    public Enemy
{
public:
	Debuffer(const Vector2D& pos);
	~Debuffer();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

