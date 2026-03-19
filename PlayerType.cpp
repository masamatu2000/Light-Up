#include "PlayerTYpe.h"
#include"AttackType.h"

void PlayerAttack::Player1Attack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}

void PlayerAttack::Player2Attack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}

void PlayerAttack::Player3Attack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}

void PlayerAttack::Player4Attack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}

void PlayerAttack::Player5Attack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}