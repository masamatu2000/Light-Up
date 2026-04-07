#include "Object.h"
#include "Enemy.h"
#include "Player.h"
#include"Boss.h"
#include"Bullet.h"
#include"Slashs.h"
#include <vector>


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

}
