#include "AttackType.h"
#include "Stage.h"
#include"Player.h"

/// <summary>
/// バレットを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

//全体に共通する定数
namespace
{
	//弾の構造体定数			　　速度　サイズ　寿命　 位置
	//プレイヤー
	const BulletType BASE_B = { 300.0f,  20.0f, 3.0f, 10.0f }; //基本プレイヤー
	const BulletType MAGE_B = { 500.0f,   10.0f, 3.0f, 10.0f }; //メイジ
	const BulletType KNIGHT_B = { 100.0f,  20.0f, 3.0f, 20.0f }; //騎士
	//敵
	const BulletType FAIRY_B = { 100.0f,  20.0f, 3.0f, 10.0f }; //妖精
	const BulletType TURRET_B = { 300.0f,  20.0f, 7.0f, 10.0f }; //タレット
	const BulletType BOMBER_B = { 300.0f,  20.0f, 7.0f, 10.0f }; //爆弾魔
}

//爆弾魔用定数
namespace Bomber
{
	//最高到達地点
	const float MAX_HEIGHT = IMAGE_SCALE * 2;
	//最高到達点までの時間	
	const float MAX_TIME = 1.0f;
}

Bullet::Bullet(const Vector2D& pos, BulletNumber bulletNum, bool lookleft, ObjectTag tag)
{
	bulletNumber = bulletNum;
	position = pos;
	islookleft = lookleft;
	objtag = tag;
	switch (bulletNumber) {
	case BulletNumber::BASE:
		bulletType = BASE_B;
		break;
	case BulletNumber::MAGE:
		bulletType = MAGE_B;
		break;
	case BulletNumber::KNIGHT:
		bulletType = KNIGHT_B;
		break;
	case BulletNumber::FAIRY:
		bulletType = FAIRY_B;
		break;
	case BulletNumber::TURRET:
		bulletType = TURRET_B;
		break;
	case BulletNumber::BOMBER:
		bulletType = BOMBER_B;
		break;
	}
	//位置を調整
	SetOffsetPosition();
	//向きの設定
	CheckDirection();
	//速度を計算
	CalculateVelocity();
}

Bullet::Bullet(const Vector2D& pos, BulletNumber bulletNum, Vector2D direction, ObjectTag tag)
	:Bullet(pos, bulletNum, false, tag)
{
	//向き、速度の上書き
	dir = direction;
	CalculateVelocity();
}

Bullet::Bullet(const Vector2D& pos, Vector2D distance, BulletNumber bulletNum, ObjectTag tag)
	:Bullet(pos, bulletNum, false, tag)
{
	dis = distance;
	CalculateGravity();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (bulletNumber == BulletNumber::BOMBER)
	{
		UpdateBomber();
		return;
	}
	//ライフがないなら処理をしない
	if (CheckNoLife())
	{
		return;
	}
	//ポジションの更新
	float dt = GetDeltaTime();
	position.x += Velocity.x * dt;
	position.y += Velocity.y * dt;

	if (HitWall())
	{
		DestroyMe();
	}
}

void Bullet::UpdateBomber()
{
	//ポジションの更新
	float dt = GetDeltaTime();
	position.x += Velocity.x * dt;
	position.y += Velocity.y * dt;
	Velocity.y += gravity * dt;

	//何かにあったたら爆発（斬撃で代用）
	if (HitWall())
	{
		new Slash(position, SlashNumber::BOMBER, false, ObjectTag::ENEMY);
		DestroyMe();
	}
}


void Bullet::Draw()
{
	float posX = position.x - Stage::scrollX;
	float posY = position.y - Stage::scrollY;
	DrawCircle((int)posX, (int)posY, (int)bulletType.rad, GetColor(255, 255, 255), TRUE);
}

void Bullet::CalculateVelocity()
{
	Velocity = Math2D::Mul(dir, bulletType.vel);
	/*float dt = GetDeltaTime();
	Velocity = Math2D::Mul(Velocity, dt);*/
}

void Bullet::CalculateGravity()
{
	float H = Bomber::MAX_HEIGHT;
	float T = Bomber::MAX_TIME;
	//重力
	gravity = (2.0f * H) / (T * T);
	//初速（Y軸）
	Velocity.y = -(gravity * T);
	//X軸の速度
	Velocity.x = dis.x / (T * 2.0f);
}

void Bullet::SetOffsetPosition()
{
	//弾をオフセット分移動させる
	//左向いてるなら
	if (islookleft)
	{
		position.x -= bulletType.offsetX;
	}
	//右向いてるなら
	else if (!islookleft)
	{
		position.x += bulletType.offsetX;
	}
	circleColid = CircleColid(Vector2D(0, 0), bulletType.rad);
}

bool Bullet::CheckNoLife()
{
	float dt = GetDeltaTime();
	if (bulletType.life > 0)
	{
		bulletType.life -= dt;
		//ライフがないなら弾を消してtrueを返す
		if (bulletType.life <= 0)
		{
			DestroyMe();
			return true;
		}
	}
	return false;
}

bool Bullet::HitWall()
{
	Stage* s = FindGameObject<Stage>();
	//右壁の判定
	int d1 = s->HitWallRight((int)(position.x + IMAGE_SCALE - 1), (int)(position.y + IMAGE_SCALE - 1));
	int d2 = s->HitWallRight((int)(position.x + IMAGE_SCALE - 1), (int)(position.y));
	int d = max(d1, d2);
	if (d > 0)
	{
		return true;
	}
	//左壁の判定
	d1 = s->HitWallLeft((int)(position.x + 0), (int)(position.y + IMAGE_SCALE - 1));
	d2 = s->HitWallLeft((int)(position.x + 0), (int)(position.y));
	d = max(d1, d2);
	if (d > 0)
	{
		return true;
	}
	//床との判定
	/*d1 = s->HitFloor((int)(position.x + 0), (int)(position.y + IMAGE_SCALE));
	d2 = s->HitFloor((int)(position.x + IMAGE_SCALE - 1), (int)(position.y + IMAGE_SCALE));
	d = max(d1, d2);
	if (d > 0)
	{
		return true;
	}*/
	//天井との判定
	/*d1 = s->HitCeiling((int)(position.x + 0), (int)(position.y - 1));
	d2 = s->HitCeiling((int)(position.x + IMAGE_SCALE - 1), (int)(position.y - 1));
	d = max(d1, d2);
	if (d > 0)
	{
		return true;
	}*/

	return false;
}