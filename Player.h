#pragma once
#include "Character.h"
#include "PlayerType.h"

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
	int GetInvincibilityTime()
	{
		return invincibilityTimeCounter;
	}
	void SetInvincibilityTime()
	{
		invincibilityTimeCounter = INVINCIBILITU_TIME;
	}

private:
	void Update() override;
	void Draw() override;
	void Attack() override;
	
	void Mova();
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
	bool IsCorpse;
	float curse; //呪い
	float curseLowerLimit;
	const int curseRecoveryArea = 100;
	int invincibilityTimeCounter;
	const int INVINCIBILITU_TIME = 120;

	//描画用関数
	int patX;//縦に何個目？
	int patY;//横に何個目？
	int patCounter;
	int attackcounter;
	bool coyotejump;

	int mainAttackRecast;
	int subAttackRecast;

	//アニメーションの状態保存
	enum AnimeState
	{
		STAND,
		WALK,
		RUN,
		JUMP
	};
	AnimeState animeState;

	//プレイ状態保存
	enum PlayState
	{
		//スタートアニメーション
		START,
		//プレイ中
		PLAY,
		//プレイヤーが死んだとき
		OVER
	};
	PlayState playState;
	//プレイ状態ごとの更新処理
	void StartUpdate();
	void PlayUpdate();
	void OverUpdate();
	//プレイ状態ごとの描画処理
	void StartDraw();
	void PlayDraw();
	void OverDraw();
};