#include "Object.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>


Object::Object()
{
}

Object::~Object()
{
}

void Object::Update()
{
	Player* pl = FindGameObject<Player>();
	Enemy* en = FindGameObject<Enemy>();
	Player* player = nullptr;

	std::vector<Enemy*> aliveEnemies;

	//敵を一回クリアしておく
	aliveEnemies.clear();

	//自分がやられていたらスルー
	if (player == nullptr||player->IsDontDestroy()== false)
	{
		return;
	}

	for (auto& enemy:aliveEnemies)
	{
		float dist = Math2D::Length(Math2D::Sub(pl->GetPosition(),en->GetPosition()));
		float collisiondist = pl->GetCollisionRadius() + en->GetCollisionRadius();

		if (dist < collisiondist)
		{
			pl->DestroyMe();

			en->DestroyMe();
		}
	}
}
