#pragma once
#include "Character.h"
#include "BossMove.h"

class Boss : public Character
{
public:
	Boss();
	Boss(const Vector2D& pos, BossNumber bNum);
	~Boss();
	BossNumber GetEnum() { return bossNumber; }
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
	BossNumber bossNumber;
	float speed;
	int invincibilityTimeCounter;
	const int INVINCIBILITU_TIME = 10 % 60;
};