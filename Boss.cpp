#include "Boss.h"
#include "Stage.h"
#include "Player.h"
#include"Gimmick.h"
/// <summary>
/// ìGÇä«óùÇ∑ÇÈ
/// M.Shoji
/// </summary>

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Update()
{

}

void Boss::Draw()
{
	if (isDebug)
	{
		float x = position.x - Stage::scrollX;
		float y = position.y - Stage::GetScrollY();

		DrawBoxAA(x, y, x + CHARACTER_IMAGE_SCALE, y + CHARACTER_IMAGE_SCALE, GetColor(255, 255, 255), FALSE);
		DrawFormatString(0, 180, GetColor(255, 255, 255), "%.0f:%.0f", Velocity.x, Velocity.y);
	}
}

void Boss::Move()
{

}

void Boss::Attack()
{
}

