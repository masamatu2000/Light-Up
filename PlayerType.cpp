#include "PlayerTYpe.h"
#include"AttackType.h"

void PlayerAttack::Player1MainAttack(const Vector2D& pos,bool lookleft)
{
	new Slash(pos, SlashNumber::BASE, lookleft,ObjectTag::PLAYER);
}

void PlayerAttack::Player2MainAttack(const Vector2D& pos,bool lookleft)
{

	new Slash(pos, SlashNumber::MAGE, lookleft, ObjectTag::PLAYER);
}

void PlayerAttack::Player3MainAttack(const Vector2D& pos,bool lookleft)
{
	new Slash(pos, SlashNumber::KNIGHT,lookleft, ObjectTag::PLAYER);
}

void PlayerAttack::Player1SubAttack(const Vector2D& pos,bool lookleft)
{
	new Bullet(pos, BulletNumber::BASE,lookleft,ObjectTag::PLAYER);
}

void PlayerAttack::Player2SubAttack(const Vector2D& pos,bool lookleft)
{
	new Bullet(pos, BulletNumber::MAGE,lookleft, ObjectTag::PLAYER);
}

void PlayerAttack::Player3SubAttack(const Vector2D& pos, bool lookleft)
{
	new Slash(pos, SlashNumber::KNIGHT, lookleft, ObjectTag::PLAYER);
	new Bullet(pos, BulletNumber::KNIGHT,lookleft, ObjectTag::PLAYER);
}
