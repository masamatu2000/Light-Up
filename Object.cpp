#include "Object.h"
#include "Enemy.h"
#include "Player.h"
#include "AttackType.h"
#include <vector>


Object::Object()
{
}

Object::~Object()
{
}

void ObjectProcess::HitObject()
{
	Player* pl = FindGameObject<Player>();
	Enemy* en = FindGameObject<Enemy>();

	//敵のベクトル
	auto aliveEnemies = FindGameObjects<Enemy>();

	auto aliveBullets = FindGameObjects<Bullet>();

	auto aliveSlashes = FindGameObjects<Slash>();



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
			//pl->DestroyMe();

			enemy->DestroyMe();
			break;
		}
	}

	//敵と弾のヒットチェック
	for (auto& bullet : aliveBullets)
	{
		for (auto& enemy : aliveEnemies)
		{
			float dist = Math2D::Length(Math2D::Sub(en->GetPosition(), bullet->GetPosition()));
			float collisiondist = en->GetCollisionRadius() + bullet->GetCollisionRadius();

			if (dist < collisiondist)
			{
				en->DestroyMe();
				bullet->DestroyMe();

			}
		}
		
	}
	//敵とスラッシュのヒットチェック
	for (auto& slash : aliveSlashes)
	{
		float dist = Math2D::Length(Math2D::Sub(en->GetPosition(), slash->GetPosition()));
		float collisiondist = en->GetCollisionRadius() + slash->GetCollisionRadius();

		if (dist < collisiondist)
		{
			en->DestroyMe();
			slash->DestroyMe();

		}
	}

}
