#include "Player.h"
#include "Stage.h"
#include "globals.h"

namespace
{
	//どのくらいの割合で重力を与えるか
	const float GRAVITY = 0.5f;//重力 （定数）
}
Player::Player()
{

}

Player::Player(int x, int y)
{
	position = Vector2D(x, y);
	Velocity.y = 0.0f;
	accel = -50.0f;//加速率
	decal = 3.0f;//減衰率

}

Player::~Player()
{
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();
	//右に進む
	if (CheckHitKey(KEY_INPUT_D))
	{
		position.x += 5.0f;
	}
	//左に進む
	if (CheckHitKey(KEY_INPUT_A))
	{
		position.x -= 5.0f;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		jamp();
	}
	//プレイヤー落下
	fall();

	//地面との当たり判定
	if (s != nullptr)
	{
		int d1 = s->HitFloor(position.x + 0, position.y + 16);
		int d2 = s->HitFloor(position.x + 16 - 1, position.y + 16);

		int d = max(d1, d2);

		if (d > 0)
		{
			position.y -= (d - 1);
			Velocity.y = 0;
			CanJump = true;
		}
		else
		{
			CanJump = false;
		}
	}
	


}

void Player::Draw()
{

	float x = position.x;
	float y = position.y;

	DrawBox(x, y, x+16, y+16, GetColor(255, 0, 0), TRUE);


}

void Player::Attack()
{
}

void Player::jamp()
{
	if (CanJump)
	{
		//初期速度の設定
		float dt = GetDeltaTime();
		Velocity.y = accel * dt;
	}

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

void Player::fall()
{
	//マイナスの値になっても減速させる、Velocityの値がマイナス　＝　落下
	float dt = GetDeltaTime();
	Velocity.y += GRAVITY * dt;

	//positionを加速度分上昇させる、位置を変える処理
	position.y += Velocity.y;
}
