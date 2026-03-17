#pragma once
#include "Character.h"
struct Curse
{
	unsigned int CurseLevel;
};
class Player : public Character
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
	void fall();

	float maxSpeed;//最高速度
	float currentSpeed;//現在の速度

	float accel;//加速度

	float decal;//減速度

	bool CanJump;


};