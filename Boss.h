#pragma once
#include "Character.h"
#include "BossMove.h"

class Boss : public Character
{
public:
	Boss();
	Boss(const Vector2D& pos, BOSS_NUMBER bNum);
	~Boss();
	BOSS_NUMBER GetEnum() { return bossNumber; }
	int GetInvincibilityTime() { return invincibilityTimeCounter; }
	void SetInvincibilityTime(int timer) { invincibilityTimeCounter = timer; }
	void SetInvincibilityTime()
	{
		invincibilityTimeCounter = INVINCIBILITU_TIME;
	}
private:
	void Update() override;
	void Draw() override;
private:
	BOSS_NUMBER bossNumber;
	float speed;
	int invincibilityTimeCounter;
	const int INVINCIBILITU_TIME = 10 % 60;
};