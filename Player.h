#pragma once
#include "Character.h"
struct Curse
{
	unsigned int CurseLevel;
};
class Player : Character
{
public:
	Player();
	Player(int x, int y);
	~Player();
private:
	void Update() override;
	void Draw() override;
	void Attack() override;

	void jamp();
	void MainAttack();
	void SubAttack();
	void SupportSkill();

};