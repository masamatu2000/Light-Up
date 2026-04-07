#include "Bomber.h"
#include"Player.h"
#include"Stage.h"
#include"Gimmick.h"
#include"Bullet.h"
#include"Slash.h"

/// <summary>
/// 爆弾魔を管理するクラス
/// </summary>
/// <author>H.suginunma</author>

//ボマー用の定数
namespace BomberData
{
	//最高到達地点
	const float MAX_HEIGHT = IMAGE_SCALE * 2;
	//最高到達点までの時間
	const float MAX_TIME = 1.0f;
}

Bomber::Bomber(const Vector2D& pos)
{
	position = pos;
	timer = 0.0f;
	invincibilityTimeCounter = 0.0f;
	enemyNumber = EnemyNumber::BOMBER;
	enemyStatus = GetEnemyStatus(enemyNumber);
	SetStatus();
}

Bomber::~Bomber()
{
}

void Bomber::Update()
{
	Enemy::Update();

	Move();
	Attack();
}

void Bomber::Draw()
{
	Enemy::Draw();
}

void Bomber::Move()
{
	//一定距離以内ならスルー
	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	//プレイヤーとの距離（ベクトル）
	Vector2D dis = Math2D::Sub(pPos, position);
	//プレイヤーとの距離（距離）
	float distance = Math2D::Length(dis);
	if (distance < enemyStatus.attackDistance)
	{
		return;
	}
	float dt = GetDeltaTime();
	//座標の更新
	position.x += Velocity.x * dt;
	position.y += Velocity.y * dt;

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

void Bomber::Attack()
{
	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	//プレイヤーとの距離（ベクトル）
	Vector2D dis = Math2D::Sub(pPos, position);
	//プレイヤーとの距離（距離）
	float distance = Math2D::Length(dis);
	//攻撃が可能かどうか
	static bool isAttack = false;

	//距離が一定以下かつ、クールタイムが終わっているなら攻撃可能に
	//この間は移動しない
	if (distance < enemyStatus.attackDistance)
	{
		if (timer > enemyStatus.coolTime)
		{
			isAttack = true;
			SetTimer(0);
		}
	}
	if (isAttack)
	{
		//放物線を描くバレットを生成
		new Bullet(position, dis, BulletNumber::BOMBER, ObjectTag::ENEMY);

		isAttack = false;
	}
}
