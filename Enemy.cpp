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
	DrawBox(400, 500, 500, 600, GetColor(0, 0, 255), TRUE);
}

void Enemy::Attack()
{
}

void Enemy::Mova()
{
}
