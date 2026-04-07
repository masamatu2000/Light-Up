#include "Turret.h"
#include"Player.h"
#include"Stage.h"
#include"Gimmick.h"
#include"Bullet.h"

/// <summary>
/// タレットを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

//タレット用の定数
namespace TurretData
{
	//タレットの継続時間
	const float SHOT_TIME = 1.0f;
}

Turret::Turret(const Vector2D& pos)
{
	position = pos;
	timer = 0.0f;
	invincibilityTimeCounter = 0.0f;
	enemyNumber = EnemyNumber::TURRET;
	enemyStatus = GetEnemyStatus(enemyNumber);
	SetStatus();
}

Turret::~Turret()
{
}

void Turret::Update()
{
	Enemy::Update();

	Attack();
}

void Turret::Draw()
{
	Enemy::Draw();
}

void Turret::Attack()
{
	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	//プレイヤーとの距離
	float distance = Math2D::Length(Math2D::Sub(pPos, position));
	//レーザーの方向ベクトル 攻撃可能になった時にだけ設定する
	static Vector2D dir = { 0,0 };
	//攻撃が可能かどうか
	static bool isAttack = false;
	//攻撃時間（1秒間）を管理する用のタイマー
	static float shotTimer = 0.0f;

	//距離が一定以下かつ、クールタイムが終わっているなら攻撃可能に
	if (timer > enemyStatus.coolTime)
	{
		if (distance <= enemyStatus.attackDistance)
		{
			isAttack = true;
			dir = Math2D::Normalize(Math2D::Sub(pPos, position));
			SetTimer(0);
		}
	}

	if (isAttack)
	{
		if (shotTimer < TurretData::SHOT_TIME)
		{
			shotTimer += gDeltaTime;
			new Bullet(position, BulletNumber::TURRET, dir, ObjectTag::ENEMY);
			if (shotTimer >= TurretData::SHOT_TIME)
			{
				shotTimer = 0.0f;
				dir = { 0,0 };
				isAttack = false;
			}
		}
	}
}
