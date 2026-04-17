#include "Kuriboh.h"
#include"Player.h"
#include"Stage.h"
#include"Gimmick.h"
#include"Slash.h"

/// <summary>
/// クリボーを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

Kuriboh::Kuriboh(const Vector2D& pos)
{
	position = pos;
	timer = 0.0f;
	invincibilityTimeCounter = 0;
	enemyNumber = EnemyNumber::KURIBOH;
	enemyStatus = GetEnemyStatus(enemyNumber);
	SetStatus();
}

Kuriboh::~Kuriboh()
{
}

void Kuriboh::Update()
{
	Enemy::Update();

	Move();
	Attack();
}

void Kuriboh::Draw()
{
	Enemy::Draw();
}

void Kuriboh::Move()
{
	Stage* s = FindGameObject<Stage>();
	Player* pl = FindGameObject<Player>();
	float dt = GetDeltaTime();

	Vector2D pPos = pl->GetPosition();
	//X軸方向の距離
	float distance = pPos.x - position.x;
	//トレース中に向かう方向
	//初期右
	float dir = 1.0f;
	//プレイヤーが左にいるなら左に
	if (distance < 0)
	{
		dir = -1.0f;
	}
	//追跡範囲内かどうか
	bool isTrace = (abs(distance) < enemyStatus.traceDistance);
	
	//追跡中の移動
	if (isTrace)
	{
		position.x += dir * abs(Velocity.x) * dt;
	}
	else
	{
		position.x += Velocity.x * dt;
	}

	//壁の判定
	//右に進んでいるとき
	if (Velocity.x > 0)
	{
		float d = CheckHitWall("RIGHT");
		if (d > 0)
		{
			//左右反転
			Velocity.x *= -1;
			position.x -= d;
		}
	}
	//左に進んでいるとき
	else if (Velocity.x < 0)
	{
		float d = CheckHitWall("LEFT");
		if (d > 0)
		{
			Velocity.x *= -1;
			position.x += d;
		}
	}

	//重力の適応
	Velocity.y += GRAVITY * dt;
	position.y += Velocity.y * dt;

	float d = CheckHitWall("DOWN");
	if (d > 0)
	{
		position.y -= (d - 1);
		Velocity.y = 0;
	}
}

void Kuriboh::Attack()
{
	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	Vector2D distance = Math2D::Sub(pPos, position);

	if (timer > enemyStatus.coolTime)
	{
		if (Math2D::Length(distance) <= enemyStatus.attackDistance)
		{
			new Slash(position, SlashNumber::KURIBOH, (distance.x < 0), ObjectTag::ENEMY);
			SetTimer(0);
		}
	}
}
