#pragma once
#include "Character.h"
#include "PlayerType.h"

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

	void SetPosition(Vector2D pos)
	{
		position = pos;
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

	bool CanJump;//ジャンプできる状態かどうか
	bool canPrevious; //前のステージに戻れるかどうか
	bool canNext; //次のステージに進めるかどうか
	PlayerName playerType;


};