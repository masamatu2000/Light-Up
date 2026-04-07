#pragma once
#include "Character.h"
#include "EnemyMove.h"

namespace
{
	const int INVINCIBILITU_TIME = 10 % 60;
}
//敵のステータス保存用の構造体
struct EnemyStatus
{
	//ヒットポイント
	int hp;
	//X軸方向の速度
	float velocityX;
};

class Enemy : public Character
{
public:
	Enemy();
	Enemy(const Vector2D &pos,EnemyNumber ENum);
	~Enemy();
	EnemyNumber GetEnum() { return enemyNumber; }
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
	void Attack() override;
	void Move() override;
	void SetStatus();
private:
	EnemyNumber enemyNumber;
	EnemyStatus enemyStatus;
	bool isTrace;
	float timer;
	int invincibilityTimeCounter;
};