#include "BossMove.h"
#include "Player.h"
#include "Boss.h"
#include"Bullet.h"
#include"Slash.h"
#include "Stage.h"

Vector2D BossMove::PhysicsCalculation(const Vector2D& position, const Vector2D& Velocity)
{
	const float GRAVITY = 9.8f * 60 * 2;//重力 （定数）	Stage* s = FindGameObject<Stage>();
	Vector2D pos = position;
	Stage* s = FindGameObject<Stage>();
	Boss* boss = FindGameObject<Boss>();
	Vector2D vel = boss->GetVel();
	
	float dt = GetDeltaTime();

	if (s != nullptr) {
		int d1 = s->HitFloor((int)(pos.x + 0), (int)(pos.y + IMAGE_SCALE));
		int d2 = s->HitFloor((int)(pos.x + IMAGE_SCALE - 1), (int)(pos.y + IMAGE_SCALE));

		int d = max(d1, d2);

		if (d > 0) {
			pos.y -= (d - 1);
			boss->SetCanJamp(true);
		}
		else
		{
			vel.y = vel.y - 0.5f;
			//if (vel.y < -10.0f)
			//{
			//	vel.y = -10.0f;
			//}
			boss->SetVel(Vector2D(0, vel.y));
		}
	}
	if (s != nullptr) {
		//天井との当たり判定
		int d1 = s->HitCeiling((int)(pos.x + 0), (int)(pos.y - 1));//yの方にも＋すると足元が天井判定されるのでなし
		int d2 = s->HitCeiling((int)(pos.x + IMAGE_SCALE - 1), (int)(pos.y - 1));

		int d = max(d1, d2);

		//天井に触れていないとジャンプをすることが出来ないのでCanJumpをコメントアウト
		if (d > 0) {
			pos.y += (d - 1);
		}
	}
	if (Velocity.x > 0) {
		int d1 = s->HitWallRight((int)(pos.x + IMAGE_SCALE - 1), (int)(pos.y + IMAGE_SCALE - 1));
		int d2 = s->HitWallRight((int)(pos.x + IMAGE_SCALE - 1), (int)(pos.y));

		int d = max(d1, d2);

		pos.x -= max(d1, d2);
	}
	else if (Velocity.x < 0)
	{
		int d1 = s->HitWallLeft((int)(pos.x + 0), (int)(pos.y + IMAGE_SCALE - 1));
		int d2 = s->HitWallLeft((int)(pos.x + 0), (int)(pos.y));

		int d = max(d1, d2);

		pos.x += max(d1, d2);
	}
	return pos;
}

void BossMove::jamp(const float& power)
{
	Boss* boss = FindGameObject<Boss>();
	Vector2D vel = boss->GetVel();
	if (boss->GetCanJamp())
	{
		boss->SetVel(Vector2D(0, power));
		boss->SetCanJamp(false);
	}
}

void BossMove::Boss01mova01()
{
	Boss* boss = FindGameObject<Boss>();
	Vector2D oldBossPos = boss->GetPosition();
	Vector2D bPos = boss->GetPosition();
	Vector2D vel = boss->GetVel();
	Player* player = FindGameObject<Player>();
	Vector2D pPos = player->GetPosition();
	int attackCounter = boss->GetAttackCounter();

	float dx = pPos.x - bPos.x;

	float distance = Math2D::Length(Math2D::Sub(bPos,pPos));
	if (distance < IMAGE_SCALE * 2)
	{
		if (attackCounter % 10 == 0 && attackCounter < 30)
		{
			new Slash(bPos, SlashNumber::BASE, (dx < 0), ObjectTag::ENEMY);
		}
	}
	else
	{
		attackCounter = 0;
	}
	if (distance > IMAGE_SCALE * 5)
	{
		jamp(15.0f);
		if ((dx < 0))
		{
			bPos.x += -10.0f;
		}
		else
		{
			bPos.x += 10.0f;
		}
	}
	else if(distance > IMAGE_SCALE * 1 && vel.y <= 0)
	{
		if ((dx < 0))
		{
			bPos.x += -3.0f;
		}
		else
		{
			bPos.x += 3.0f;
		}
	}
	attackCounter++;
	bPos.y += vel.y * -1;
	Vector2D velosity = Math2D::Sub(bPos, oldBossPos);
	bPos = PhysicsCalculation(bPos, velosity);
	boss->SetPosition(bPos);
	boss->SetAttackCounter(attackCounter);
}

void BossMove::Boss01mova02()
{
	Boss* boss = FindGameObject<Boss>();
	Vector2D oldBossPos = boss->GetPosition();
	Vector2D bPos = boss->GetPosition();
	Vector2D vel = boss->GetVel();
	Player* player = FindGameObject<Player>();
	Vector2D pPos = player->GetPosition();
	int attackCounter = boss->GetAttackCounter();

	float dx = pPos.x - bPos.x;

	float distance = Math2D::Length(Math2D::Sub(bPos, pPos));
	if (distance < IMAGE_SCALE * 2)
	{
		if (attackCounter % 10 == 0)
		{
			new Slash(bPos, SlashNumber::BASE, (dx < 0), ObjectTag::ENEMY);
		}
	}
	else
	{
		if (attackCounter % 1 == 0)
		{
			Vector2D direction;
			int baseAngle = 300 * (DX_PI / 180);
			direction = Vector2D(cos(baseAngle) + cos(baseAngle + (DX_PI / 2))* (sin(attackCounter * 0.5) * tan(40 * (DX_PI / 180))), 
				sin(baseAngle) + sin(baseAngle + (DX_PI / 2)) * (sin(attackCounter * 0.5) * tan(40 * (DX_PI / 180))));
			direction = Math2D::Normalize(direction);
			new Bullet(bPos, BulletNumber::FAIRY, direction, ObjectTag::ENEMY);
		}
	}
	attackCounter++;
	bPos.y += vel.y * -1;
	Vector2D velosity = Math2D::Sub(bPos, oldBossPos);
	bPos = PhysicsCalculation(bPos, velosity);
	boss->SetPosition(bPos);
	boss->SetAttackCounter(attackCounter);
}

void BossMove::Boss01mova03()
{
	Boss* boss = FindGameObject<Boss>();
	Vector2D oldBossPos = boss->GetPosition();
	Vector2D bPos = boss->GetPosition();
	Vector2D vel = boss->GetVel();
	Player* player = FindGameObject<Player>();
	Vector2D pPos = player->GetPosition();
	int attackCounter = boss->GetAttackCounter();

	float dx = pPos.x - bPos.x;

	float distance = Math2D::Length(Math2D::Sub(bPos, pPos));
	if (distance < IMAGE_SCALE * 2)
	{
		if (attackCounter % 10 == 0 && attackCounter < 30)
		{
			new Slash(bPos, SlashNumber::BASE, (dx < 0), ObjectTag::ENEMY);
		}
	}
	else
	{
		attackCounter = 0;
	}
	if (distance > IMAGE_SCALE * 5)
	{
		
		if ((dx < 0))
		{
			bPos.x += -10.0f;
		}
		else
		{
			bPos.x += 10.0f;
		}
	}
	else if (distance > IMAGE_SCALE * 1 && vel.y <= 0)
	{
		if ((dx < 0))
		{
			bPos.x += -3.0f;
		}
		else
		{
			bPos.x += 3.0f;
		}
	}
	attackCounter++;
	bPos.y += vel.y * -1;
	Vector2D velosity = Math2D::Sub(bPos, oldBossPos);
	bPos = PhysicsCalculation(bPos, velosity);
	boss->SetPosition(bPos);
	boss->SetAttackCounter(attackCounter);
}
