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

void ObjectProcess::HitObject()
{
	Player* pl = FindGameObject<Player>();

	auto aliveEnemies = FindGameObjects<Enemy>();

	//Ž©•ª‚ª‚â‚ç‚ê‚Ä‚¢‚½‚çƒXƒ‹[
	if (pl == nullptr)
	{
		return;
	}

	for (auto& enemy:aliveEnemies)
	{
		float dist = Math2D::Length(Math2D::Sub(pl->GetPosition(), enemy->GetPosition()));
		float collisiondist = pl->GetCollisionRadius() + enemy->GetCollisionRadius();

		if (dist < collisiondist)
		{
			//pl->DestroyMe();

			enemy->DestroyMe();
		}
	}
}
