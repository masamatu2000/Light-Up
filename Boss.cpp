#include "Boss.h"
#include "Stage.h"
#include "Player.h"
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

Boss::Boss(const Vector2D& pos, BOSS_NUMBER bNum)
{
	position = pos;
	circleColid = CircleColid(Vector2D(IMAGE_SCALE / 2, IMAGE_SCALE / 2), IMAGE_SCALE / 2);
	bossNumber = bNum;
	Velocity = BOSS_SPEED;
	speed = Velocity.x;
	switch (bossNumber) {
	case BOSS01:
		Hp = BossTypeNum::BOSS_01_HP;
		break;
	case BOSS02:
		Hp = BossTypeNum::BOSS_02_HP;
		break;
	}
}

Boss::~Boss()
{
}

void Boss::Update()
{
	if (Hp <= 0)
	{
		DestroyMe();
	}
}

void Boss::Draw()
{
	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::scrollY;

	DrawBox(x, y, x + IMAGE_SCALE, y + IMAGE_SCALE, GetColor(255, 255, 255), TRUE);
}

