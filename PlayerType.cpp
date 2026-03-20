#include "PlayerTYpe.h"
#include"AttackType.h"

void PlayerAttack::Player1MainAttack(const Vector2D& pos)
{
	new Slash(pos, SLASH_NUMBER::slash01);
}

void PlayerAttack::Player2MainAttack(const Vector2D& pos)
{
	new Slash(pos, SLASH_NUMBER::slash01);
}

void PlayerAttack::Player3MainAttack(const Vector2D& pos)
{
	new Slash(pos, SLASH_NUMBER::slash01);
}

void PlayerAttack::Player1SubAttack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}

void PlayerAttack::Player2SubAttack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}

void PlayerAttack::Player3ubAttack(const Vector2D& pos)
{
	new Bullet(pos, BULLET_NUMBER::bullet01);
}
