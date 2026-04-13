#include "Object.h"
#include "Enemy.h"
#include "Player.h"
#include"Boss.h"
#include"Bullet.h"
#include"Slash.h"
#include"Laser.h"
#include <vector>
#include<cmath>


Object::Object()
{
}

Object::~Object()
{
}

void ObjectProcess::HitObject()
{
	const int Damage = 1;

	Player* pl = FindGameObject<Player>();
	//Enemy* en = FindGameObject<Enemy>();

	//敵のベクトル
	auto aliveEnemies = FindGameObjects<Enemy>();

	auto aliveBullets = FindGameObjects<Bullet>();

	auto aliveSlashes = FindGameObjects<Slash>();

	auto aliveLaseres = FindGameObjects<Laser>();

	Boss* bs = FindGameObject<Boss>();

	//自分がやられていたらスルー
	if (pl == nullptr)
	{
		return;
	}

	//敵と自機のヒットチェック
	for (auto& enemy:aliveEnemies)
	{
		float dist = Math2D::Length(Math2D::Sub(pl->GetPosition(), enemy->GetPosition()));
		float collisiondist = pl->GetCollisionRadius() + enemy->GetCollisionRadius();

		if (dist < collisiondist)
		{
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
			break;
		}
	}

	//ボスと自機のヒットチェック
	if (bs != nullptr) {
		float dist = Math2D::Length(Math2D::Sub(pl->GetPosition(), bs->GetPosition()));
		float collisiondist = pl->GetCollisionRadius() + bs->GetCollisionRadius();

		if (dist < collisiondist)
		{
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
	}

	//敵と弾のヒットチェック
	for (auto& bullet : aliveBullets)
	{
		//通常の敵との判定
		for (auto& enemy : aliveEnemies)
		{
			if (bullet->Gettag() == ObjectTag::PLAYER) {
				float dist = Math2D::Length(Math2D::Sub(enemy->GetPosition(), bullet->GetPosition()));
				float collisiondist = enemy->GetCollisionRadius() + bullet->GetCollisionRadius();

				if (dist < collisiondist)
				{
					if (enemy->GetInvincibilityTime() < 0)
					{
						enemy->DownHp(Damage);
						bullet->DestroyMe();
						enemy->SetInvincibilityTime();
					}
				}
			}
		}
		//ボスとの判定
		if (bs != nullptr) {
			if (bullet->Gettag() == ObjectTag::PLAYER) {
				float dist = Math2D::Length(Math2D::Sub(bs->GetPosition(), bullet->GetPosition()));
				float collisiondist = bs->GetCollisionRadius() + bullet->GetCollisionRadius();
				if (dist < collisiondist)
				{
					bs->DownHp(Damage);
					bullet->DestroyMe();
				}
			}
		}
	}
	//敵と弾のヒットチェック
	for (auto& bullet : aliveBullets)
	{
		//通常の敵との判定
			if (bullet->Gettag() == ObjectTag::ENEMY) {
				float dist = Math2D::Length(Math2D::Sub(pl->GetPosition(), bullet->GetPosition()));
				float collisiondist = pl->GetCollisionRadius() + bullet->GetCollisionRadius();

				if (dist < collisiondist)
				{
					//ボマーの弾は当たった時に爆発するように、ヒットしたときにスラッシュを生成
					if (bullet->GetBulletNum() == BulletNumber::BOMBER)
					{
						Vector2D pos = bullet->GetPosition();
						new Slash(pos, SlashNumber::BOMBER, false, ObjectTag::ENEMY);
					}
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
					bullet->DestroyMe();
					break;
				}
			}
		//ボスとの判定
		if (bs != nullptr) {
			if (bullet->Gettag() == ObjectTag::BOSS) {
				float dist = Math2D::Length(Math2D::Sub(pl ->GetPosition(), bullet->GetPosition()));
				float collisiondist = pl->GetCollisionRadius() + bullet->GetCollisionRadius();
				if (dist < collisiondist)
				{
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
					bullet->DestroyMe();
				}
			}
		}
	}
	//敵とスラッシュのヒットチェック
	for (auto& slash : aliveSlashes)
	{
		//通常の敵との判定
		for (auto& enemy : aliveEnemies)
		{
			if (slash->Gettag() == ObjectTag::PLAYER) {
				float dist = Math2D::Length(Math2D::Sub(enemy->GetPosition(), slash->GetPosition()));
				float collisiondist = enemy->GetCollisionRadius() + slash->GetCollisionRadius();

				if (dist < collisiondist)
				{
					if (enemy->GetInvincibilityTime() < 0) {
						enemy->DownHp(Damage);
						slash->DestroyMe();
						enemy->SetInvincibilityTime();
					}
				}
			}
		}
		//ボスとの判定
		if (bs != nullptr) {
			if (slash->Gettag() == ObjectTag::PLAYER) {
				float dist = Math2D::Length(Math2D::Sub(bs->GetPosition(), slash->GetPosition()));
				float collisiondist = bs->GetCollisionRadius() + slash->GetCollisionRadius();
				if (dist < collisiondist)
				{
					bs->DownHp(Damage);
					slash->DestroyMe();
				}
			}
		}
		if (slash->Gettag() == ObjectTag::ENEMY) {
			float dist = Math2D::Length(Math2D::Sub(pl->GetPosition(), slash->GetPosition()));
			float collisiondist = pl->GetCollisionRadius() + slash->GetCollisionRadius();

			if (dist < collisiondist)
			{
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
				break;
			}
		}
		//ボスとの判定
		if (bs != nullptr) {
			if (slash->Gettag() == ObjectTag::BOSS) {
				float dist = Math2D::Length(Math2D::Sub(pl->GetPosition(), slash->GetPosition()));
				float collisiondist = pl->GetCollisionRadius() + slash->GetCollisionRadius();
				if (dist < collisiondist)
				{
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
					slash->DestroyMe();
				}
			}
		}

	}

	//レーザーとのヒットチェック
	for (auto& laser : aliveLaseres)
	{
		//プレイヤーとの判定
		if (laser->Gettag() == ObjectTag::ENEMY) {
			float dist = laser->GetDist(laser->GetLineStart(), laser->GetLineEnd(), pl->GetPosition());
			float collisiondist = pl->GetCollisionRadius() + laser->GetCollisionLineRadius();

			if (dist < collisiondist)
			{
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
				break;
			}
		}
	}
}

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