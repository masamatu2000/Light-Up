#include "Santana.h"
#include "Stage.h"
#include"Gimmick.h"
#include"Corpse.h"
#include "Player.h"
#include "AttackType.h"

namespace
{
	const float TRACE_DISTANCE = 32 * 4;
	const Vector2D BOSS_SPEED = Vector2D(15, 0);
	const int HP = 10;
}

Santana::Santana()
{
	
}

Santana::Santana(const Vector2D& pos)
{
	position = pos;
	circleColid = CircleColid(Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2), CHARACTER_IMAGE_SCALE / 2);
	Velocity = BOSS_SPEED;
	speed = Velocity.x;
	Hp = HP;
	invincibilityTimeCounter = 0;//無敵時間
	canJamp = true;
	attackCounter = 0;
}

Santana::~Santana()
{
}

void Santana::Update()
{
	  Move();

	if (Hp <= 0)
	{
		new  Corpse(position, GimmickType::CORPSE, "Boss", BossNumber::BOSS01);
		Stage* s = FindGameObject<Stage>();
		s->DefeatedBoss();
		DestroyMe();
	}
	invincibilityTimeCounter--;
}

void Santana::Draw()
{
	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::GetScrollY();

	DrawBoxAA(x, y, x + CHARACTER_IMAGE_SCALE, y + CHARACTER_IMAGE_SCALE, GetColor(255, 255, 255), TRUE);
	DrawFormatString(0,  180, GetColor(255, 255, 255), "%.0f:%.0f", Velocity.x,Velocity.y);
}

void Santana::Move()
{
	attackCounter++;
	
	if (Hp > 7)
	{
		mova01();
	}
	else if (Hp > 4)
	{
		mova02();
	}
	else
	{
		mova03();
	}
	if (canJamp == false)
	{
		Velocity.y = Velocity.y + 0.5f;
	}
	position = Math2D::Add(position, Velocity);
	PhysicsCalculation();
}

void Santana::Attack()
{
}

void Santana::PhysicsCalculation()
{
	const float GRAVITY = 9.8f * 60 * 2;//重力 （定数）	Stage* s = FindGameObject<Stage>();
	Stage* s = FindGameObject<Stage>();

	float dt = GetDeltaTime();

	if (s != nullptr) {
		int d1 = s->HitFloor((int)(position.x + 0), (int)(position.y + CHARACTER_IMAGE_SCALE));
		int d2 = s->HitFloor((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y + CHARACTER_IMAGE_SCALE));

		int d = max(d1, d2);

		if (d > 0) {
			position.y -= (d - 1);
			Velocity.y = 0;
			canJamp = true;
		}
		else
		{
			Velocity.y = Velocity.y + 0.5f;
			//if (vel.y < -10.0f)
			//{
			//	vel.y = -10.0f;
			//}
		}
	}
	if (s != nullptr) {
		//天井との当たり判定
		int d1 = s->HitCeiling((int)(position.x + 0), (int)(position.y - 1));//yの方にも＋すると足元が天井判定されるのでなし
		int d2 = s->HitCeiling((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y - 1));

		int d = max(d1, d2);

		//天井に触れていないとジャンプをすることが出来ないのでCanJumpをコメントアウト
		if (d > 0) {
			position.y += (d - 1);
		}
	}
	if (Velocity.x > 0) {
		int d1 = s->HitWallRight((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
		int d2 = s->HitWallRight((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y));

		int d = max(d1, d2);

		position.x -= max(d1, d2);
	}
	else if (Velocity.x < 0)
	{
		int d1 = s->HitWallLeft((int)(position.x + 0), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
		int d2 = s->HitWallLeft((int)(position.x + 0), (int)(position.y));

		int d = max(d1, d2);

		position.x += max(d1, d2);
	}
}

void Santana::jamp(const float& power)
{
	if (canJamp)
	{
		Velocity.y = power * -1;
		canJamp = false;
	}
}

void Santana::mova01()
{
	Player* player = FindGameObject<Player>();
	Vector2D pPos = player->GetPosition();
	//自身の中心の位置
	Vector2D Apos = Math2D::Add(position, Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2));

	float dx = pPos.x - position.x;

	float distance = Math2D::Length(Math2D::Sub(position, pPos));
	if (distance < IMAGE_SCALE * 2)
	{
		if (attackCounter % 10 == 0 && attackCounter < 30)
		{
			new Slash(Apos, SlashNumber::BASE, (dx < 0), ObjectTag::ENEMY);
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
			Velocity.x = -10.0f;
		}
		else
		{
			Velocity.x = 10.0f;
		}
	}
	else if (distance > IMAGE_SCALE * 1 )
	{
		if (canJamp)
		{
			if ((dx < 0))
			{
				Velocity.x = -3.0f;
			}
			else
			{
				Velocity.x = 3.0f;
			}
		}
		else
		{
			if (Velocity.x < -3.0f)
			{
				Velocity.x += 0.5f;
			}
			else if (Velocity.x > 3.0f)
			{
				Velocity.x -= 0.5f;
			}
		}

	}
	else
	{
		Velocity.x = 0;
	}
}

void Santana::mova02()
{
	Player* player = FindGameObject<Player>();
	Vector2D pPos = player->GetPosition();
	//自身の中心の位置
	Vector2D Apos = Math2D::Add(position, Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2));

	float dx = pPos.x - position.x;

	float distance = Math2D::Length(Math2D::Sub(position, pPos));
	if (distance < IMAGE_SCALE * 2)
	{
		if (attackCounter % 10 == 0)
		{
			new Slash(Apos, SlashNumber::BASE, (dx < 0), ObjectTag::ENEMY);
		}
	}
	else
	{
		if (attackCounter % 1 == 0)
		{
			float Pi = (float)DX_PI;
			Vector2D direction;
			float baseAngle = 300 * (Pi / 180);
			direction = Vector2D((float)cos(baseAngle) + (float)cos(baseAngle + (Pi / 2)) * ((float)sin(attackCounter * 0.5) * (float)tan(40 * (Pi / 180))),
				(float)sin(baseAngle) + (float)sin(baseAngle + (Pi / 2)) * ((float)sin(attackCounter * 0.5) * (float)tan(40 * (Pi / 180))));
			direction = Math2D::Normalize(direction);
			new Bullet(Apos, BulletNumber::FAIRY, direction, ObjectTag::ENEMY);
		}
	}
}

void Santana::mova03()
{
	Player* player = FindGameObject<Player>();
	Vector2D pPos = player->GetPosition();
	//自身の中心の位置
	Vector2D Apos = Math2D::Add(position, Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2));

	float dx = pPos.x - position.x;

	float distance = Math2D::Length(Math2D::Sub(position, pPos));
	if (distance < IMAGE_SCALE * 2)
	{
		if (attackCounter % 10 == 0 && attackCounter < 30)
		{
			new Slash(Apos, SlashNumber::BASE, (dx < 0), ObjectTag::ENEMY);
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
			Velocity.x = -10.0f;
		}
		else
		{
			Velocity.x = 10.0f;
		}
	}
	else if (distance > IMAGE_SCALE * 1)
	{
		if ((dx < 0))
		{
			Velocity.x = -3.0f;
		}
		else
		{
			Velocity.x = 3.0f;
		}
	}
	else
	{
		Velocity.x = 0.0f;
	}
}

