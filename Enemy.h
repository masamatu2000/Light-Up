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
	void SetTimer(int time) { timer = time; }//攻撃用のタイマーセッター
	int GetInvincibilityTime() { return invincibilityTimeCounter; }
	void SetInvincibilityTime(int timer) { invincibilityTimeCounter = timer; }
	void SetInvincibilityTime()
	{
		invincibilityTimeCounter = INVINCIBILITU_TIME;
	}
private:
	void Update() override;
	void Draw() override;
private:
	ENEMY_NUMBER EnemyNumber;
	bool IsTrace;
	int timer;
	int invincibilityTimeCounter;
	const int INVINCIBILITU_TIME = 10 % 60;
};