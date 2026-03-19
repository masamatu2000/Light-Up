#include "Player.h"
#include "Stage.h"
#include "globals.h"

/// <summary>
/// M.Shoji
/// </summary>
namespace
{
	//どのくらいの割合で重力を与えるか
	const float GRAVITY = 9.8f * 60;//重力 （定数）
	const int IMAGE_SCALE = 16;
	const float JUMP_HEIGHT = 4.0f*IMAGE_SCALE;
	const float accel = 2.0f;//加速率
	const float decal = 1.5f;//減衰率
	const float maxSpeed = 15.0f;//最高速度
}
Player::Player()
{
	CanJump = true;

	canPrevious = false;
	canNext = false;
	playerType = Name1;
}

Player::Player(int x, int y)
{
	position = Vector2D(x, y);
	Velocity = Vector2D(0.0f,0.0f);
	circleColid = CircleColid(Vector2D(8.0f, 8.0f), 8.0f);
	
	CanJump = true;
	canPrevious = false;
	canNext = false;
	playerType = Name1;
}

Player::~Player()
{
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();
	float dt = GetDeltaTime();
	//右に進む
	if (CheckHitKey(KEY_INPUT_D)) {
		//position.x += 3.0f; 加速度を変えて移動していくのでコメントアウト

		
		//徐々に加速していく
		Velocity.x += accel * dt;
		if (Velocity.x > maxSpeed)
		{
			Velocity.x = maxSpeed;
		}

	}
	//値がマイナスの時
	//左に進む
	else if (CheckHitKey(KEY_INPUT_A)) {
		//position.x -= 3.0f;

		
		//徐々に加速していく(プラスの処理）
		Velocity.x -= accel * dt;
		if (Velocity.x < -maxSpeed)
		{
			Velocity.x = -maxSpeed;
		}
	}
	else
	{
		//徐々に減速させる
		if (Velocity.x > 0)//現在のスピードが正のとき
		{
			Velocity.x -= decal * dt;
			if (Velocity.x < 0)//現在のスピードが正かつマイナスになった =0になった
			{
				Velocity.x = 0;
			}
		}

		if (Velocity.x < 0)//現在のスピードがマイナスなとき
		{
			Velocity.x += decal * dt;
			if (Velocity.x > 0)
			{
				Velocity.x = 0;
			}
		}
	}
	//位置を変える
	position.x += Velocity.x;

	if (Velocity.x > 0){
		int d1 = s->HitWallRight(position.x + IMAGE_SCALE - 1, position.y + IMAGE_SCALE - 1);
		int d2 = s->HitWallRight(position.x + IMAGE_SCALE - 1, position.y);

		int d = max(d1, d2);
		if (d > 0)
		{
			Velocity.x = 0;
		}

		position.x -= max(d1, d2);
	}
	else if(Velocity.x < 0)
	{
		int d1 = s->HitWallLeft(position.x + 0, position.y + IMAGE_SCALE - 1);
		int d2 = s->HitWallLeft(position.x + 0, position.y);

		int d = max(d1, d2);
		if (d > 0)
		{
			Velocity.x = 0;
		}

		position.x += max(d1, d2);
	}

	if (CheckHitKey(KEY_INPUT_SPACE)){
		jamp();
	}
	//プレイヤー落下
	fall();

	//地面との当たり判定
	if (s != nullptr){
		int d1 = s->HitFloor(position.x + 0, position.y + IMAGE_SCALE);
		int d2 = s->HitFloor(position.x + IMAGE_SCALE - 1, position.y + IMAGE_SCALE);

		int d = max(d1, d2);

		if (d > 0){
			position.y -= (d - 1);
			Velocity.y = 0;
			CanJump = true;
		}
		else{
			CanJump = false;
		}
	}
	if (s != nullptr) {
		//天井との当たり判定
		int d1 = s->HitCeiling(position.x + 0, position.y - 1);//yの方にも＋すると足元が天井判定されるのでなし
		int d2 = s->HitCeiling(position.x + IMAGE_SCALE - 1, position.y - 1);

		int d = max(d1, d2);

		//天井に触れていないとジャンプをすることが出来ないのでCanJumpをコメントアウト
		if (d > 0) {
			position.y += (d - 1);
			Velocity.y = 0;
		}
	}

	Interact();
	
	Scroll();

	Attack();
	ObjectProcess::HitObject();
}

void Player::Draw()
{
	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::scrollY;

	DrawBox(x, y, x+16, y+16, GetColor(255, 0, 0), TRUE);

	DrawFormatString(0, 0, 0xffffff, "次：%d 前：%d", canNext, canPrevious);
	DrawFormatString(0, 30, 0xffffff, "X：%.0f　Y:%.0f",position.x,position.y);
}

void Player::Attack()
{
	if (Input::IsKeyDown(KEY_INPUT_M))
	{
		MainAttack();
	}
}

void Player::jamp()
{

	if (CanJump){
		//初期速度の設定
		float InitialVelocity = -std::sqrt(2.0f * GRAVITY * JUMP_HEIGHT);
		Velocity.y = InitialVelocity;//dtは正の値でジャンプさせるには負の値にする必要あり
	}

}


void Player::MainAttack()
{
	switch (playerType)
	{
	case(Name1):
		PlayerAttack::Player1Attack(position);
		break;
	default:
		break;
	}
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
	if (dt < 1.1f)
	{
		Velocity.y += GRAVITY * dt;

		//positionを加速度分上昇させる、位置を変える処理
		position.y += Velocity.y * dt;
	}
}

void Player::Interact()
{
	Stage* s = FindGameObject<Stage>();
	//ステージのインタラクト
	canPrevious = s->CanChangeStage(position, "previous");
	canNext = s->CanChangeStage(position, "next");

	if (Input::IsKeyDown(KEY_INPUT_E))
	{
		if (canNext)
		{
			s->NextStage();
		}
		else if (canPrevious)
		{
			s->PreviousStage();
		}
	}
}

void Player::Scroll()
{
	// スクロール処理
	if (position.x >= 100) {
		Stage::scrollX = position.x - 100;
	}

	if (position.y - Stage::scrollY <= 100) {
		Stage::scrollY = position.y - 100;
	}

	//より自然？なスクロール
	if (position.y - Stage::scrollY >= 150) {
		Stage::scrollY = position.y - 150;
	}

	//スクロールの制限
	//左端
	if (Stage::scrollX < Stage::mapLeft)
	{
		Stage::scrollX = Stage::mapLeft;
	}
	//右端
	if (Stage::scrollX > Stage::mapRight)
	{
		Stage::scrollX = Stage::mapRight;
	}

	//上端
	if (Stage::scrollY < Stage::mapTop)
	{
		Stage::scrollY = Stage::mapTop;
	}

	//下端
	if (Stage::scrollY > Stage::mapBottom)
	{
		Stage::scrollY = Stage::mapBottom;
	}
}
