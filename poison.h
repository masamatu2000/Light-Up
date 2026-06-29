#pragma once
#include "Enemy.h"
class poison :
    public Enemy
{
public:
	poison(const Vector2D& pos);
	~poison();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

