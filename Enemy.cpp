#include "Enemy.h"
#include "Stage.h"
#include "Player.h"

/// <summary>
/// “G‚ğŠÇ—‚·‚é
/// M.Shoji
/// </summary>
Enemy::Enemy()
{
}

Enemy::Enemy(int x, int y)
{
	position = Vector2D(x, y);



}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	
}

void Enemy::Draw()
{
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::scrollY;

	DrawBox(positionx,positiony,positionx + 16,positiony + 16, GetColor(0, 0, 255), TRUE);
	DrawFormatString(20, 20, GetColor(255, 255, 255),"%f %f",position.x,position.y,TRUE);//•Ï”‚ğo—Í‚·‚é
}

void Enemy::Attack()
{
}

void Enemy::Mova()
{
}
