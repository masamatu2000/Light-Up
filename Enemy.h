#pragma once
#include "Character.h"

namespace
{
	const int INVINCIBILITU_TIME = 10 % 60;
}

enum class EnemyNumber
{
	KURIBOH,
	FAIRY,
	TURRET,
	GUNDAM,
	BOMBER,
	CREEPER,
	DOKUTARO,
	DEBUFFER,
	LANCER,
	BERSERKER
};

//敵のステータス保存用の構造体
struct EnemyStatus
{
	//ヒットポイント
	int hp;
	//X軸方向の速度
	float velocityX;
	//クールタイム
	float coolTime;
	//当たり判定のサイズ
	float rad;
	//攻撃距離
	float attackDistance;
	//トレースし始める距離
	float traceDistance;
};

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();
	EnemyNumber GetEnum() { return enemyNumber; }
	void SetTimer(float time) { timer = time; }//攻撃用のタイマーセッター
	int GetInvincibilityTime() { return invincibilityTimeCounter; }
	void SetInvincibilityTime(int timer) { invincibilityTimeCounter = timer; }
	void SetInvincibilityTime()
	{
		invincibilityTimeCounter = INVINCIBILITU_TIME;
	}
protected:
	void Update() override;
	void Draw() override;
	void Attack() override;
	void Move() override;
	//取得したステータスを変数にセット
	void SetStatus();
	//EnemyNumberからステータスを取得する
	EnemyStatus GetEnemyStatus(EnemyNumber eNum);
	//壁との判定
	float CheckHitWall(std::string wall);
protected:
	EnemyNumber enemyNumber;
	EnemyStatus enemyStatus;
	float timer;
	int invincibilityTimeCounter;
};