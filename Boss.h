#pragma once
#include "Character.h"

enum BossNumber
{
	BOSS01,
	BOSS02,
	BOSS03,
	BOSS04,
	BOSS05,
};

class Boss : public Character
{
public:
	Boss();
	~Boss();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack()override;
protected:
	BossNumber bossNumber;
	float speed;
	int invincibilityTimeCounter;
	const int INVINCIBILITU_TIME = 10 % 60;
	bool canJamp;
	int attackCounter;
};