#include "Object.h"
#include "Enemy.h"
#include "Player.h"
#include"Boss.h"
#include"Bullet.h"
#include"Slash.h"
#include"Laser.h"
#include <vector>
#include<cmath>
#include "Stage.h"

namespace
{
	//攻撃によるダメージ
	const int DAMAGE = 1;
}

Object::Object()
{
	circleColid = CircleColid();
	lineColid = LineColid();
}

Object::~Object()
{
}

void ObjectProcess::HitObject()
{
	//プレイヤーのポインタ
	Player* pl = FindGameObject<Player>();
	//敵すべてのポインタ
	auto aliveEnemies = FindGameObjects<Enemy>();
	//ボスのポインタ
	Boss* bs = FindGameObject<Boss>();
	//発動している攻撃のポインタ
	auto triggerAttackes = FindGameObjects<AttackObject>();

	//当たり判定用の変数
	float dist;
	float collisionDist;
	
	//プレイヤーが死んでいたらスルー
	if (pl == nullptr)
	{
		return;
	}

	//攻撃とキャラクターの当たり判定
	for (auto& attack : triggerAttackes)
	{
		//攻撃がプレイヤーによるものなら
		if (attack->Gettag() == ObjectTag::PLAYER)
		{
			//通常の敵との判定
			for (auto enemy : aliveEnemies)
			{
				dist = Math2D::Length(Math2D::Sub(Math2D::Add(enemy->GetPosition(), enemy->GetCollisionCenterPosition()), attack->GetPosition()));
				collisionDist = enemy->GetCollisionRadius() + attack->GetCollisionRadius();

				if (dist < collisionDist)
				{
					if (enemy->GetInvincibilityTime() < 0)
					{
						enemy->DownHp(DAMAGE);
						attack->DestroyMe();
						enemy->SetInvincibilityTime();
					}
				}
			}
			//ボスとの判定
			if (bs != nullptr)
			{
				dist = Math2D::Length(Math2D::Sub(Math2D::Add(bs->GetPosition(), bs->GetCollisionCenterPosition()), attack->GetPosition()));
				collisionDist = bs->GetCollisionRadius() + attack->GetCollisionRadius();
				if (dist < collisionDist)
				{
					bs->DownHp(DAMAGE);
					attack->DestroyMe();
				}
			}
		}

		//攻撃が敵、またはボスによるものなら
		if (attack->Gettag() == ObjectTag::ENEMY || attack->Gettag() == ObjectTag::BOSS)
		{
			//攻撃の種類を判定
			//斬撃、弾による攻撃なら
			if (attack->GetCollisionRadius() != -1.0f)
			{
				dist = Math2D::Length(Math2D::Sub(Math2D::Add(pl->GetPosition(), pl->GetCollisionCenterPosition()), attack->GetPosition()));
				collisionDist = pl->GetCollisionRadius() + attack->GetCollisionRadius();

				if (dist < collisionDist)
				{
					//弾の種類が爆弾魔のものなら
					Bullet* bl = dynamic_cast<Bullet*>(attack);
					if (bl != nullptr && bl->GetBulletNum() == BulletNumber::BOMBER)
					{
						Vector2D pos = bl->GetPosition();
						new Slash(pos, SlashNumber::BOMBER, false, ObjectTag::ENEMY);
					}
					//他の斬撃、弾は通常の処理
					PlayerTakeDamage();
					attack->DestroyMe();
					break;
				}
			}
			//レーザーによる攻撃なら
			else if (attack->GetCollisionLineRadius() != -1.0f)
			{
				dist = attack->GetDist(attack->GetLineStart(), attack->GetLineEnd(), Math2D::Add(pl->GetPosition(), pl->GetCollisionCenterPosition()));
				collisionDist = pl->GetCollisionRadius() + attack->GetCollisionLineRadius();

				if (dist < collisionDist)
				{
					PlayerTakeDamage();
					break;
				}
			}
		}
	}
}

void ObjectProcess::PlayerTakeDamage()
{
	//プレイヤーのポインタ
	Player* pl = FindGameObject<Player>();

	//プレイヤーにダメージを与える処理
	if (pl->GetInvincibilityTime() < 0)
	{
		pl->UpCurseLowerLimit(20.0f);
		if (pl->GetCurse() < pl->GetCurseLowerLimit())
		{
			pl->SetCurse(pl->GetCurseLowerLimit());
		}
		if (pl->GetCurse() >= 100.0f)
		{
			pl->SetHp(0);
		}
		pl->SetInvincibilityTime();
	}
}

//void ObjectProcess::AttackForPlayer(const AttackObject* attack)
//{
//	//敵すべてのポインタ
//	auto aliveEnemies = FindGameObjects<Enemy>();
//	//ボスのポインタ
//	Boss* bs = FindGameObject<Boss>();
//	
//	//通常の敵との判定
//	for (auto& enemy : aliveEnemies)
//	{
//		float dist = Math2D::Length(Math2D::Sub(Math2D::Add(enemy->GetPosition(), enemy->GetCollisionCenterPosition()), bullet->GetPosition()));
//		float collisiondist = enemy->GetCollisionRadius() + bullet->GetCollisionRadius();
//
//		if (dist < collisiondist)
//		{
//			if (enemy->GetInvincibilityTime() < 0)
//			{
//				enemy->DownHp(DAMAGE);
//				bullet->DestroyMe();
//				enemy->SetInvincibilityTime();
//			}
//		}
//	}
//}

//void ObjectProcess::AttackForEnemy(const AttackObject* attack)
//{
//	//プレイヤーのポインタ
//	Player* pl = FindGameObject<Player>();
//}

float Object::GetDist(Vector2D start,Vector2D end, Vector2D target)
{
	//線分のベクトル
	Vector2D line = Math2D::Sub(end, start);
	//線分の長さの２条
	float lineLengthSq = Math2D::LengthSq(line);

	//最短距離の計算
	//最短地点が線分のどこか（比率）
	float t = ((target.x - start.x) * line.x + (target.y - start.y) * line.y) / lineLengthSq;
	//tを制限
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	if (t > 1.0f)
	{
		t = 1.0f;
	}

	//線分の最短座標を計算
	Vector2D nearPos = Math2D::Add(start, Math2D::Mul(line, t));
	//距離を計算
	Vector2D dist = Math2D::Sub(target, nearPos);
	return sqrt(dist.x * dist.x + dist.y * dist.y);
}

