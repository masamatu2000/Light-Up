#pragma once
#include"Enemy.h"

class Kuriboh : public Enemy
{
public:
	Kuriboh(const Vector2D& pos);
	~Kuriboh();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

