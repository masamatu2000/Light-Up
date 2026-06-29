#pragma once
#include "Enemy.h"
class Lancer :
    public Enemy
{
public:
	Lancer(const Vector2D& pos);
	~Lancer();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

