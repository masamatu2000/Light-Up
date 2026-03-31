#include "Boss.h"
#include "Stage.h"
#include "Player.h"
#include"Gimmick.h"
#include"BossMove.h"
/// <summary>
/// ìGÇä«óùÇ∑ÇÈ
/// M.Shoji
/// </summary>
namespace {
	const float TRACE_DISTANCE = 32 * 4;
	const Vector2D BOSS_SPEED = Vector2D(15, 0);
}
Boss::Boss()
{
}

Boss::Boss(const Vector2D& pos, BossNumber bNum)
{
	position = pos;
	circleColid = CircleColid(Vector2D(IMAGE_SCALE / 2, IMAGE_SCALE / 2), IMAGE_SCALE / 2);
	bossNumber = bNum;
	Velocity = BOSS_SPEED;
	speed = Velocity.x;
	switch (bossNumber) {
	case BOSS01:
		Hp =(unsigned int) BossTypeNum::BOSS_01_HP;
		break;
	case BOSS02:
		Hp = (unsigned int)BossTypeNum::BOSS_02_HP;
		break;
	}
	invincibilityTimeCounter = 0;//ñ≥ìGéûä‘
	canJamp = true;
	attackCounter = 0;
}

Boss::~Boss()
{
}

void Boss::Update()
{
	Mova();
	if (Hp <= 0)
	{
		new  Gimmick(position, GIMMICK_TYPE::Corpse, "Boss", bossNumber);
		Stage* s = FindGameObject<Stage>();
		s->DefeatedBoss();
		DestroyMe();
	}
	invincibilityTimeCounter--;
}

void Boss::Draw()
{
	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::scrollY;

	DrawBoxAA(x, y, x + IMAGE_SCALE, y + IMAGE_SCALE, GetColor(255, 255, 255), TRUE);
}

void Boss::Mova()
{
	switch (bossNumber)
	{
	case BOSS01:
		if (Hp > 7)
		{
			BossMove::Boss01mova01();
		}
		else if (Hp > 4)
		{
			BossMove::Boss01mova02();
		}
		else
		{
			BossMove::Boss01mova03();
		}
		break;
	case BOSS02:
		break;
	case BOSS03:
		break;
	case BOSS04:
		break;
	case BOSS05:
		break;
	default:
		break;
	}
}

