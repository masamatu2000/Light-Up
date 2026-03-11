#pragma once
#include "Character.h"
#include "BossMove.h"

class Boss : Character
{
public:
	Boss();
	~Boss();
private:
	void Update() override;
	void Draw() override;
	void Attack() override;
private:
	BOSS_NUMBER BossNumber;
};