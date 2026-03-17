#include "Player.h"
#include "Stage.h"
#include "globals.h"

namespace
{
	//どのくらいの割合で重力を与えるか
	const float GRAVITY = 0.25f;//重力 （定数）
}
Player::Player()
{

}

Player::Player(int x, int y)
{
	position = Vector2D(x, y);
	Velocity.y = 0.0f;
	accel = 5.0f;//加速率
	decal = 0.15f;//減衰率
	maxSpeed = 30.0f;
	currentSpeed = 0.0f;

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
		position.x += 3.0f;

		//右の壁との当たり判定
		int d1 = s->HitWallRight(position.x + 0, position.y + 15);
		int d2 = s->HitWallRight(position.x + 16, position.y + 15);

		position.x -= max(d1, d2);

		//徐々に加速していく
		//currentSpeed += accel;
		//if (currentSpeed > maxSpeed){
		//	currentSpeed = maxSpeed;
		//}
		////減速していって最後は0で止まる
		//else{
		//	currentSpeed -= decal;
		//	if (currentSpeed < 0) {
		//		currentSpeed = 0;
		//	}
		//}
	}
	//左に進む
	if (CheckHitKey(KEY_INPUT_A))
	{
		position.x -= 3.0f;

		//左の壁との当たり判定
		int d1 = s->HitWallLeft(position.x + 0, position.y + 15);
		int d2 = s->HitWallLeft(position.x + 16, position.y + 15);

		position.x += max(d1, d2);

		//徐々に加速していく
		//currentSpeed += accel;
		//if (currentSpeed > maxSpeed) {
		//	currentSpeed = maxSpeed;
		//}
		////減速していって最後は0で止まる
		//else {
		//	currentSpeed -= decal;
		//	if (currentSpeed < 0) {
		//		currentSpeed = 0;
		//	}
		//}
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
		if (s != nullptr)
		{
			//天井との当たり判定
			int d1 = s->HitCeiling(position.x + 0, position.y);//yの方にも＋すると足元が天井判定されるのでなし
			int d2 = s->HitCeiling(position.x + 16 - 1, position.y);

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
