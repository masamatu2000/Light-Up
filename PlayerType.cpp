#include "PlayerTYpe.h"
#include"AttackType.h"

void PlayerAttack::Player1MainAttack(const Vector2D& pos,bool lookleft)
{
	new Slash(pos, SLASH_NUMBER::slash01, lookleft);
}

void PlayerAttack::Player2MainAttack(const Vector2D& pos,bool lookleft)
{

	new Slash(pos, SLASH_NUMBER::slash02, lookleft);
}

void PlayerAttack::Player3MainAttack(const Vector2D& pos,bool lookleft)
{
	new Slash(pos, SLASH_NUMBER::slash03,lookleft);
}

void PlayerAttack::Player1SubAttack(const Vector2D& pos,bool lookleft)
{
	new Bullet(pos, BULLET_NUMBER::bullet01,lookleft);
}

void PlayerAttack::Player2SubAttack(const Vector2D& pos,bool lookleft)
{
	new Bullet(pos, BULLET_NUMBER::bullet02,lookleft);
}

void PlayerAttack::Player3SubAttack(const Vector2D& pos, bool lookleft)
{
	new Bullet(pos, BULLET_NUMBER::bullet03,lookleft);
}
