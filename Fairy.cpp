#include "Fairy.h"
#include"Player.h"
#include"Stage.h"
#include"Gimmick.h"
#include"Bullet.h"

/// <summary>
/// 妖精を管理するクラス
/// </summary>
/// <author>H.suginunma</author>

Fairy::Fairy(const Vector2D& pos)
{
	position = pos;
	timer = 0.0f;
	invincibilityTimeCounter = 0.0f;
	enemyNumber = EnemyNumber::FAIRY;
	enemyStatus = GetEnemyStatus(enemyNumber);
	SetStatus();
}

Fairy::~Fairy()
{
}

void Fairy::Update()
{
	Enemy::Update();

	Move();
	Attack();
}

void Fairy::Draw()
{
	Enemy::Draw();
}

void Fairy::Move()
{
	Stage* s = FindGameObject<Stage>();
	float dt = GetDeltaTime();
	//Y軸移動の制御タイマー
	static float t = 0.0f;

	//Y軸方向の移動
	position.y = position.y + 1.0f * sinf(15.0f * t);
	t = t + gDeltaTime;
	//X軸方向の移動
	position.x += Velocity.x * dt;

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


}

void Fairy::Attack()
{
	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	Vector2D distance = Math2D::Sub(pPos, position);

	if (timer > enemyStatus.coolTime)
	{
		if (Math2D::Length(distance) <= enemyStatus.attackDistance)
		{
			Vector2D dir = Math2D::Normalize(distance);
			float Rad = 30 * (DX_PI_F / 180.0f);
			Vector2D Rotation = { (dir.x * cosf(Rad) - dir.y * sinf(Rad)),(dir.x * sinf(Rad) + dir.y * cosf(Rad)) };
			Vector2D Rotation2 = { (dir.x * cosf(-Rad) - dir.y * sinf(-Rad)),(dir.x * sinf(-Rad) + dir.y * cosf(-Rad)) };
			new Bullet(position, BulletNumber::FAIRY, dir, ObjectTag::ENEMY);
			new Bullet(position, BulletNumber::FAIRY, Rotation, ObjectTag::ENEMY);
			new Bullet(position, BulletNumber::FAIRY, Rotation2, ObjectTag::ENEMY);
			SetTimer(0);
		}
	}
}
