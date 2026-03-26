#pragma once
/// <summary>
/// akimotomasaki
/// </summary>
#include"Math2D.h"
#include<vector>

enum ENEMY_NUMBER
{
	Enemy01,
	Enemy02,
	Enemy03,
	Enemy04,
	Enemy05,
	Enemy06,
};
class Enemy;
namespace EnemyTypeNum
{
	const float ENEMY_01_HP = 2.0f;
	const float ENEMY_02_HP = 2.0f;
}
namespace EnemyAttack {
	
	void Enemy1Attack(const Vector2D& pos,const Vector2D& vel,const int &timer);
	void Enemy2Attack(const Vector2D& pos,const Vector2D& vel, const int& timer);
	void Enemy3Attack(const Vector2D& pos,const Vector2D& vel, const int& timer);
	void Enemy4Attack(const Vector2D& pos,const Vector2D& vel, const int& timer);
	void Enemy5Attack(const Vector2D& pos,const Vector2D& vel, const int& timer);
}
