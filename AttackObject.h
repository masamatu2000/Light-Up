#pragma once
#include "Character.h"

enum ATTACK_TYPE
{
	bullet,
	slash
};
enum BULLET_NUMBER
{
	bullet01,
	bullet02
};
enum SLASH_NUMBER
{
	slash01,
	slash02
};
class AttackObject : public Character
{
public:
	AttackObject();
	~AttackObject();
public:
	void Update() override;
	void Draw() override;
	void Attack() override;
protected:
	ATTACK_TYPE attackType;
	BULLET_NUMBER bulletNumber;
	SLASH_NUMBER slashNumber;
};