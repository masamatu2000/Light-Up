#pragma once
#include "Math2D.h"

enum BossNumber
{
	BOSS01,
	BOSS02,
	BOSS03,
	BOSS04,
	BOSS05,
};

namespace BossTypeNum
{
	const float BOSS_01_HP = 10.0f;
	const float BOSS_02_HP = 10.0f;
}

namespace BossMove
{
	Vector2D PhysicsCalculation(const Vector2D& position,const Vector2D& Velocity);
	void jamp(const float& power);
	void Boss01mova01();
	void Boss01mova02();
	void Boss01mova03();
}