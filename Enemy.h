#pragma once
#include "Character.h"
#include "EnemyMove.h"

class Enemy : public Character
{
public:
	Enemy();
	Enemy(const Vector2D &pos,ENEMY_NUMBER ENum);
	~Enemy();
private:
	void Update() override;
	void Draw() override;
	void Attack() override;

	void Mova();
private:
	ENEMY_NUMBER EnemyNumber;
};