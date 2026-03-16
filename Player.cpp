#include "Player.h"
#include "Object.h"

Player::Player()
{
}

Player::Player(int x, int y)
{
	position = Vector2D(x, y);
}

Player::~Player()
{
}

void Player::Update()
{
	//âEÇ…êiÇﬁ
	if (CheckHitKey(KEY_INPUT_D))
	{
		position.x += 2.0f;
	}
	//ç∂Ç…êiÇﬁ
	if (CheckHitKey(KEY_INPUT_A))
	{
		position.x -= 2.0f;
	}
}

void Player::Draw()
{
	DrawBox(300, 400, 500, 600, GetColor(255, 0, 0), TRUE);


}

void Player::Attack()
{
}

void Player::jamp()
{
}

void Player::MainAttack()
{
}

void Player::SubAttack()
{
}

void Player::SupportSkill()
{
}
