#pragma once
#include "Character.h"

enum class AttackType
{
	BULLET,
	SLASH
};
enum class ObjectTag 
{
	PLAYER,
	ENEMY,
	BOSS
};
enum class BulletNumber
{
	BASE,
	MAGE,
	KNIGHT,
	FAIRY,
	TURRET,
	BOMBER
};
enum class SlashNumber
{
	BASE,
	MAGE,
	KNIGHT,
	KURIBOH,
	BOMBER
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
	ObjectTag Gettag() { return objtag; }
protected:
	AttackType attackType;
	bool islookleft;
	ObjectTag objtag;
	//方向ベクトル 初期値右方向に設定
	Vector2D dir = { 1.0f,0.0f };
protected:
	//向きを計算
	void CheckDirection();
	//速度計算用の関数
	virtual void CalculateVelocity() {}
	//方向により発射位置の調整
	virtual void SetOffsetPosition() {}
	//ライフの計算、識別
	virtual bool CheckNoLife()
	{
		return false;
	}
};