#pragma once
#include "Character.h"
#include "EnemyMove.h"

class Enemy : public Character
{
public:
	Enemy();
	Enemy(const Vector2D &pos,ENEMY_NUMBER ENum);
	~Enemy();
	ENEMY_NUMBER GetEnum() { return EnemyNumber; }
private:
	void Update() override;
	void Draw() override;
private:
	ENEMY_NUMBER EnemyNumber;
	bool IsTrace;
	float Speed;
};