#pragma once
#include"Math2D.h"

enum PlayerName {
	Name1,
	Name2,
	Name3
};
namespace PlayerAttack{
	void Player1MainAttack(const Vector2D& pos,bool lookleft);//プレイヤーのポジションと、プレイヤーの移動速度を持たせる
	void Player2MainAttack(const Vector2D& pos,bool lookleft);
	void Player3MainAttack(const Vector2D& pos,bool lookleft);
	void Player1SubAttack(const Vector2D& pos, bool lookleft);
	void Player2SubAttack(const Vector2D& pos,bool lookleft);
	void Player3SubAttack(const Vector2D& pos,bool lookleft);

	
}