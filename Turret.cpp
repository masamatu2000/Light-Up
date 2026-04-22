#include "Turret.h"
#include"Player.h"
#include"Stage.h"
#include"Gimmick.h"
#include"Laser.h"

/// <summary>
/// タレットを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

//タレット用の定数
namespace TurretData
{
	//タレットの継続時間
	const float SHOT_TIME = 1.0f;
	//レーザーの長さ
	const int LASER_LENGTH = 1000;
}

Turret::Turret(const Vector2D& pos)
{
	position = pos;
	timer = 0.0f;
	invincibilityTimeCounter = 0;
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
	//攻撃が可能かどうか
	static bool isAttack = false;
	//攻撃時間（1秒間）を管理する用のタイマー
	static float shotTimer = 0.0f;
	//自身の中心の位置
	Vector2D Apos = Math2D::Add(position, Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2));

	//距離が一定以下かつ、クールタイムが終わっているなら攻撃可能に
	if (timer > enemyStatus.coolTime)
	{
		if (distance <= enemyStatus.attackDistance)
		{
			isAttack = true;
			SetTimer(0);
		}
	}

	if (isAttack)
	{
		//レーザーの生成
		new Laser(Apos, pPos, LaserNumber::TURRET,false, ObjectTag::ENEMY);
		isAttack = false;
	}
}
