#pragma once
#include "Character.h"
#include "PlayerType.h"
enum PLAYER_STATE
{
	STAND,
	WALK,
	RUN,
	JUMP
};

class Player : public Character
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void SetPosition(Vector2D pos)
	{
		position = pos;
	}
	bool GetKillBoss()
	{
		return killBoss;
	}
	//デバッグ用の仮の関数
	void SetKillBoss(bool kill)
	{
		killBoss = kill;
	}
	void UpCurse(float downcurse)
	{ 
		curse += downcurse; 
	}
	void SetCurse(float downcurse)
	{
		curse = downcurse;
	}
	float GetCurse() 
	{ 
		return curse; 
	}
	void UpCurseLowerLimit(float downcurse)
	{
		curseLowerLimit += downcurse;
	}
	float GetCurseLowerLimit()
	{
		return curseLowerLimit;
	}
	int GetCurseRecoveryArea()
	{
		return curseRecoveryArea;
	}
private:
	void Update() override;
	void Draw() override;
	void Attack() override;
	

	void jamp();
	void MainAttack();
	void SubAttack();
	void SupportSkill();
	void fall();
	void Interact();
	void Scroll();
	

	bool CanJump;//ジャンプできる状態かどうか
	bool canPrevious; //前のステージに戻れるかどうか
	bool canNext; //次のステージに進めるかどうか
	bool islookleft;//左を向いているかどうか
	PlayerName playerType;
	PLAYER_STATE playerState;
	bool killBoss; //ボスを倒したらステージを進むためにフラグをtrueに

	float curse; //呪い
	float curseLowerLimit;
	const int curseRecoveryArea = 100;

	//描画用関数
	int patX;//縦に何個目？
	int patY;//横に何個目？
	int patCounter;
};