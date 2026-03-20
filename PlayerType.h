#pragma once
#include"Math2D.h"

enum PlayerName {
	Name1,
	Name2,
	Name3
};
namespace PlayerAttack{
	void Player1MainAttack(const Vector2D& pos);
	void Player2MainAttack(const Vector2D& pos);
	void Player3MainAttack(const Vector2D& pos);
	void Player1SubAttack(const Vector2D& pos);
	void Player2SubAttack(const Vector2D& pos);
	void Player3ubAttack(const Vector2D& pos);
	
}