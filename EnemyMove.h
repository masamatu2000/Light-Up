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
	TURRET,
	GUNDAM,
	BOMBER,
	CREEPER,
	DOKUTARO,
	DEBUFFER,
	LANCER,
	BERSERKER
};
class Enemy;
namespace EnemyTypeNum
{
	const float ENEMY_01_HP = 2.0f;
	const float ENEMY_02_HP = 2.0f;
	const float TURRET_HP = 3.0f;
	const float BOMBER_HP = 1.0f;
	const float BOMBER_VELOCITY_X = IMAGE_SCALE;
}
namespace EnemyAttack {
	
	void Enemy1Attack(const Vector2D& pos,const Vector2D& vel,const int &timer);
	void Enemy2Attack(const Vector2D& pos,const Vector2D& vel, const int& timer);
	void TurretAttack(const Vector2D& pos, const int& timer);
	void BomberAttack(const Vector2D& pos, const Vector2D& vel, const int& timer);
}
