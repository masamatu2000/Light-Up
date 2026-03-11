#pragma once
#include "Character.h"
#include "attackType.h"

class AttackObject : Character
{
public:
	AttackObject();
	~AttackObject();
private:
	void Update() override;
	void Draw() override;
	void Attack() override;
private:
	ATTACK_TYPE attackType;
	BULLET_NUMBER bulletNumber;
	SLASH_NUMBER slashNumber;
};