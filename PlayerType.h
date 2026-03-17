#pragma once
#include"Math2D.h"
#include"AttackType.h"
enum Name {
	Name1,
	Name2,
	Name3,
	Name4,
	Name5
};
namespace {
	void Player1Attack(const Vector2D &pos){
		new Bullet(pos,BULLET_NUMBER::bullet01);
	}
	void Player2Attack(const Vector2D& pos) {
		new Bullet(pos, BULLET_NUMBER::bullet01);
	}
	void Player3Attack(const Vector2D& pos) {
		new Bullet(pos, BULLET_NUMBER::bullet01);
	}
	void Player4Attack(const Vector2D& pos) {
		new Bullet(pos, BULLET_NUMBER::bullet01);
	}
	void Player5Attack(const Vector2D& pos) {
		new Bullet(pos, BULLET_NUMBER::bullet01);
	}
}