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
	Turret,
	Gundam,
	Bomber,
	Creeper,
	Dokutaro,
	Debuffer,
	Lancer,
	Berserker
};
class Enemy;
namespace EnemyTypeNum
{
	const float ENEMY_01_HP = 2.0f;
	const float ENEMY_02_HP = 2.0f;
	const float TURRET_HP = 3.0f;
}
namespace EnemyAttack {
	
	void Enemy1Attack(const Vector2D& pos,const Vector2D& vel,const int &timer);
	void Enemy2Attack(const Vector2D& pos,const Vector2D& vel, const int& timer);
	void TurretAttack(const Vector2D& pos, const int& timer);
}
