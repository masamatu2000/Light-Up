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
	bool GetKillBoss()
	{
		return killBoss;
	}
	//デバッグ用の仮の関数
	void SetKillBoss(bool kill)
	{
		killBoss = kill;
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
	PlayerName playerType;
	bool killBoss; //ボスを倒したらステージを進むためにフラグをtrueに

	float curse; //呪い
};