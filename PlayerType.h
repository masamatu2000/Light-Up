#pragma once
#include"Math2D.h"

enum PlayerName {
	Name1,
	Name2,
	Name3,
	Name4,
	Name5
};
namespace PlayerAttack{
	void Player1Attack(const Vector2D& pos);
	void Player2Attack(const Vector2D& pos);
	void Player3Attack(const Vector2D& pos);
	void Player4Attack(const Vector2D& pos);
	void Player5Attack(const Vector2D& pos);
}