#pragma once
/// <summary>
/// akimotomasaki
/// </summary>
enum ENEMY_NUMBER
{
	Enemy01,
	Enemy02,
	Enemy03,
	Enemy04,
	Enemy05,
	Enemy06,
};
namespace EnemyAttack {
	void Enemy1Attack(const Vector2D& pos);
	void Enemy2Attack(const Vector2D& pos);
	void Enemy3Attack(const Vector2D& pos);
	void Enemy4Attack(const Vector2D& pos);
	void Enemy5Attack(const Vector2D& pos);
}