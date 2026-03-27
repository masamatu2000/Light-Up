#include "EnemyMove.h"
#include"Math2D.h"
#include"Player.h"
#include"Stage.h"
#include"Enemy.h"
#include"AttackType.h"
namespace {
	const float TRACE_DISTANCE = 32 * 10;
	const int ENEMY_BULLET_COOLTIME = 60 * 2;
}
void EnemyAttack::Enemy1Attack(const Vector2D& pos, const Vector2D& vel,const int &timer)
{
	Vector2D epos = pos;
	Vector2D evel = vel;
	auto e=FindGameObjects<Enemy>();
	Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	float dx = ppos.x - epos.x;
	float dist = abs(dx);
	bool IsAttack = false;
	if (dist < TRACE_DISTANCE) {
		float speed = abs(vel.x);
		float dt = GetDeltaTime();
		// Åö å¸Ç´ÇæÇØåàÇﬂÇÈ
		float dir = (dx > 0) ? 1.0f : -1.0f;
		epos.x += dir * speed*dt;
	}
	else {
		float dt = GetDeltaTime();
		Stage* stage = FindGameObject<Stage>();
		epos.x += vel.x * dt;
		if (vel.x > 0) {
			int d1 = stage->HitWallRight(pos.x + IMAGE_SCALE - 1, pos.y + IMAGE_SCALE - 1);
			int d2 = stage->HitWallRight(pos.x + IMAGE_SCALE - 1, pos.y);

			int d = max(d1, d2);
			if (d > 0)
			{
				evel.x *= -1;
			}

			epos.x -= max(d1, d2);
		}
		else if (vel.x < 0)
		{
			int d1 = stage->HitWallLeft(pos.x + 0, pos.y + IMAGE_SCALE - 1);
			int d2 = stage->HitWallLeft(pos.x + 0, pos.y);

			int d = max(d1, d2);
			if (d > 0)
			{
				evel.x *= -1;
			}

			epos.x += max(d1, d2);
		}
		int d1 = stage->HitFloor(pos.x + 0, pos.y + IMAGE_SCALE);
		int d2 = stage->HitFloor(pos.x + IMAGE_SCALE - 1, pos.y + IMAGE_SCALE);

		int d = max(d1, d2);

		if (d > 0) {
			epos.y -= (d - 1);
			evel.y = 0;
		}
		
	}
	if (timer > ENEMY_BULLET_COOLTIME) {
		IsAttack = true;
		//íeä€î≠éÀ
		new Bullet(pos, BULLET_NUMBER::bullet01, dx > 0,OBJECT_TAG::ENEMY);
	}
	for (auto enemy : e) {
		if (enemy->GetEnum() == Enemy01) {
			enemy->SetPosition(epos);
			enemy->SetVel(evel);
			if (IsAttack) {
				enemy->SetTimer(0);
			}
		}
	}
	
}

void EnemyAttack::Enemy2Attack(const Vector2D& pos,const Vector2D & vel,const int &timer)
{
	Vector2D epos = pos;
	Vector2D evel = vel;
	Player* pl = FindGameObject<Player>();
	auto e = FindGameObjects<Enemy>();
	static float t = 0.0f;
	epos.y = epos.y +1.0f * sinf(15.0f * t);//è„â∫Ç…ìÆÇ≠Ç‚Ç¬
	t = t + gDeltaTime;
	float dt = GetDeltaTime();
	Stage* stage = FindGameObject<Stage>();
	epos.x += evel.x * dt;
	bool IsAttack = false;
	Vector2D ppos = pl->GetPosition();
	float dx = ppos.x - epos.x;
	if (evel.x > 0) {
		int d1 = stage->HitWallRight(epos.x + IMAGE_SCALE - 1, epos.y + IMAGE_SCALE - 1);
		int d2 = stage->HitWallRight(epos.x + IMAGE_SCALE - 1, epos.y);

		int d = max(d1, d2);
		if (d > 0)
		{
			evel.x *= -1;
		}

		epos.x -= max(d1, d2);
	}
	else if (evel.x < 0)
	{
		int d1 = stage->HitWallLeft(epos.x + 0, epos.y + IMAGE_SCALE - 1);
		int d2 = stage->HitWallLeft(epos.x + 0, epos.y);

		int d = max(d1, d2);
		if (d > 0)
		{
			evel.x *= -1;
		}

		epos.x += max(d1, d2);
	}
	int d1 = stage->HitFloor(epos.x + 0, epos.y + IMAGE_SCALE);
	int d2 = stage->HitFloor(epos.x + IMAGE_SCALE - 1, epos.y + IMAGE_SCALE);

	int d = max(d1, d2);

	if (d > 0) {
		epos.y -= (d - 1);
		evel.y = 0;
	}
	if (timer > ENEMY_BULLET_COOLTIME) {
		IsAttack = true;
		new Bullet(pos, BULLET_NUMBER::bullet01, dx > 0,OBJECT_TAG::ENEMY);
	}
	for (auto enemy : e) {
		if (enemy->GetEnum() == Enemy02) {
			enemy->SetPosition(epos);
			enemy->SetVel(evel);
			if (IsAttack) {
				enemy->SetTimer(0);
			}
		}
	}
	
}

void EnemyAttack::Enemy3Attack(const Vector2D& pos, const Vector2D& vel,const int &timer)
{
}

void EnemyAttack::Enemy4Attack(const Vector2D& pos, const Vector2D& vel, const int& timer)
{
}

void EnemyAttack::Enemy5Attack(const Vector2D& pos, const Vector2D& vel, const int& timer)
{
}
