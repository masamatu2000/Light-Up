#pragma once
#include "Boss.h"

class Santana :
    public Boss
{
public:
	Santana();
	Santana(const Vector2D& pos);
	~Santana();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack()override;

	void PhysicsCalculation();
	void jamp(const float& power);
	void mova01();
	void mova02();
	void mova03();
};

