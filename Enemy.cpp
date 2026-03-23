#include "Enemy.h"
#include "Stage.h"
#include "Player.h"

/// <summary>
/// ìGÇä«óùÇ∑ÇÈ
/// M.Shoji
/// </summary>
namespace {
	const float TRACE_DISTANCE = 16 * 15;
	const Vector2D ENEMY_SPEED = Vector2D(15, 0);
	const float LEFT_LIMIT = 50.0f;
	const float RIGHT_LIMIT = (float)(WIN_WIDTH - 50);
}
Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2D& pos, ENEMY_NUMBER ENum)
{
	position = pos;
	circleColid = CircleColid(Vector2D(8.0f, 8.0f), 8.0f);
	EnemyNumber = ENum;
	Velocity = ENEMY_SPEED;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D Distance = Math2D::Sub(ppos, position);
	float dist = Math2D::Length(Distance);
	switch (EnemyNumber) {
	case Enemy01:
		if (dist < TRACE_DISTANCE) {
			Distance = Math2D::Normalize(Distance);
			float dt = GetDeltaTime();
			position.x+= Distance.x*Velocity.x*dt;
		}
		else {
			float dt = GetDeltaTime();
			Stage* stage = FindGameObject<Stage>();
			position.x += Velocity.x * dt;
			if (Velocity.x > 0) {
				int d1 = stage->HitWallRight(position.x + IMAGE_SCALE - 1, position.y + IMAGE_SCALE - 1);
				int d2 = stage->HitWallRight(position.x + IMAGE_SCALE - 1, position.y);

				int d = max(d1, d2);
				if (d > 0)
				{
					Velocity.x *= -1;
				}

				position.x -= max(d1, d2);
			}
			else if (Velocity.x < 0)
			{
				int d1 = stage->HitWallLeft(position.x + 0, position.y + IMAGE_SCALE - 1);
				int d2 = stage->HitWallLeft(position.x + 0, position.y);

				int d = max(d1, d2);
				if (d > 0)
				{
					Velocity.x *= -1;
				}

				position.x += max(d1, d2);
			}
		}
		break;
	case Enemy02:
		static float t = 0.0f;
		position.y = position.y+ 10.0f * sin(20.0f * t);//è„â∫Ç…ìÆÇ≠Ç‚Ç¬
		t = t + gDeltaTime;
		float dt = GetDeltaTime();
		Stage* stage = FindGameObject<Stage>();
		position.x += Velocity.x * dt;
		if (Velocity.x > 0) {
			int d1 = stage->HitWallRight(position.x + IMAGE_SCALE - 1, position.y + IMAGE_SCALE - 1);
			int d2 = stage->HitWallRight(position.x + IMAGE_SCALE - 1, position.y);

			int d = max(d1, d2);
			if (d > 0)
			{
				Velocity.x *= -1;
			}

			position.x -= max(d1, d2);
		}
		else if (Velocity.x < 0)
		{
			int d1 = stage->HitWallLeft(position.x + 0, position.y + IMAGE_SCALE - 1);
			int d2 = stage->HitWallLeft(position.x + 0, position.y);

			int d = max(d1, d2);
			if (d > 0)
			{
				Velocity.x *= -1;
			}

			position.x += max(d1, d2);
		}
		break;
	}
}

void Enemy::Draw()
{
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::scrollY;

	DrawBox(positionx,positiony,positionx + 16,positiony + 16, GetColor(0, 0, 255), TRUE);
	DrawFormatString(20, 20, GetColor(255, 255, 255),"%f %f",position.x,position.y,TRUE);//ïœêîÇèoóÕÇ∑ÇÈ
}

void Enemy::Attack()
{
}

void Enemy::Mova()
{
}
