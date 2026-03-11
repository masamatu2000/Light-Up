#pragma once
#include "Character.h"
#include "EnemyMove.h"

class Enemy : Character
{
public:
	Enemy();
	~Enemy();
private:
	void Update() override;
	void Draw() override;
	void Attack() override;

	void Mova();
private:
	ENEMY_NUMBER EnemyNumber;
};