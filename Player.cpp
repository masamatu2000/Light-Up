#include "Player.h"
#include "Stage.h"
#include "globals.h"
#include"ImageManager.h"
#include "DataHolder.h"
#include "Enemy.h"
#include"Boss.h"
#include"Gimmick.h"
/// <summary>
/// M.Shoji
/// </summary>
namespace
{
	//どのくらいの割合で重力を与えるか
	const float GRAVITY = 9.8f * 60 * 2;//重力 （定数）
	const float JUMP_HEIGHT = 4.0f*IMAGE_SCALE;
	const float accel = 20.0f;//加速率
	const float decal = 10.0f;//減衰率
	const float maxSpeed = 5.0f;//最高速度

	const float curseMax = 100.0f;
	const float curseDownRatio = 500.0f;
	const float cursUpIsPlayer01SubAtttack = 5.0f;
	const float cursUpIsPlayer02SubAtttack = 1.0f;
	const float cursUpIsPlayer03SubAtttack = 10.0f;
	int pushM;
	int pushB;
}
Player::Player()
{
	CanJump = true;

	canPrevious = false;
	canNext = false;
	playerType = Name1;

	curse = 0;
	killBoss = false;

	patX = 0;
	patY = 0;
	patCounter = 0;
}

Player::Player(int x, int y)
{
	position = Vector2D((float)x, (float)y);
	Velocity = Vector2D(0.0f,0.0f);
	circleColid = CircleColid(Vector2D(IMAGE_SCALE / 2, IMAGE_SCALE / 2), IMAGE_SCALE / 2);
	
	CanJump = true;
	canPrevious = false;
	canNext = false;

	curse = 0;
	curseLowerLimit = 0;
	killBoss = false;

	patX = 0;
	patY = 0;
	patCounter = 0;
	Image* image = FindGameObject<Image>();
	hImage = image->ReturnImage("player");
	DataHolder* dh = FindGameObject<DataHolder>();
	playerType = (PlayerName)(dh->playerNum - 1);
	IsCorpse = false;
	playerState = STAND;

	Hp = 1;
	invincibilityTimeCounter = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	Mova();

	Interact();
	
	Scroll();

	Attack();
	ObjectProcess::HitObject();

	//敵に近づいた時の呪いの減少
	auto aliveEnemies = FindGameObjects<Enemy>();
	for (auto& enemy : aliveEnemies)
	{
		float dist = Math2D::Length(Math2D::Sub(GetPosition(), enemy->GetPosition()));
		float collisiondist = (float)GetCurseRecoveryArea();

		if (dist < collisiondist)
		{
			float UpData = collisiondist - dist;
			UpData = UpData / curseDownRatio;
			UpData = UpData * -1;
			UpCurse(UpData);
			if (GetCurse() < GetCurseLowerLimit())
			{
				SetCurse(GetCurseLowerLimit());
			}
			break;
		}
	}
	//ボスに近づいた時の呪い減少
	Boss* bs = FindGameObject<Boss>();
	if (bs != nullptr)
	{
		float dist = Math2D::Length(Math2D::Sub(GetPosition(), bs->GetPosition()));
		float collisiondist = (float)GetCurseRecoveryArea();

		if (dist < collisiondist)
		{
			float UpData = collisiondist - dist;
			UpData = UpData / curseDownRatio;
			UpData = UpData * -1;
			UpCurse(UpData);
			if (GetCurse() < GetCurseLowerLimit())
			{
				SetCurse(GetCurseLowerLimit());
			}
		}
	}

	if (curseLowerLimit > curseMax)
	{
		curseLowerLimit = curseMax;
	}
	if (curse > curseMax)
	{
		curse = curseMax;
	}

	//無敵時間の減少
	invincibilityTimeCounter--;
}

void Player::Draw()
{
	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::scrollY;
	if (invincibilityTimeCounter > 0)
	{
		DrawBoxAA(x, y, x + IMAGE_SCALE, y + IMAGE_SCALE, GetColor(100, 100, 100), true);
	}
	switch (playerType)
	{
	case(Name1):
		DrawBoxAA(x, y, x + IMAGE_SCALE, y + IMAGE_SCALE, GetColor(255, 0, 0), false);
		break;
	case(Name2):
		DrawBoxAA(x, y, x + IMAGE_SCALE, y + IMAGE_SCALE, GetColor(0, 255, 0), false);
		break;
	case(Name3):
		DrawBoxAA(x, y, x + IMAGE_SCALE, y + IMAGE_SCALE, GetColor(0, 0, 255), false);
		break;
	default:
		break;
	}

	if (islookleft)
	{
		patY = 4;
	}
	else
	{
		patY = 0;
	}
	switch (playerState)
	{
	case(STAND):
		break;
	case(WALK):
		patY += 1;
		break;
	case(RUN):
		patY += 2;
		break;
	case(JUMP):
		patY += 3;
		break;
	default:
		break;
	}
	//DrawBox(x, y, x+IMAGE_SCALE, y+IMAGE_SCALE, GetColor(255, 0, 0), TRUE);
	DrawRectGraph((int)x, (int)y, IMAGE_SCALE * patX, IMAGE_SCALE * patY, IMAGE_SCALE, IMAGE_SCALE, hImage, TRUE);

	DrawFormatString(0, 0, 0xffffff, "次：%d 前：%d", canNext, canPrevious);
	DrawFormatString(0, 30, 0xffffff, "X：%.0f　Y:%.0f",x,y);
	DrawFormatString(0, 150, 0xffffff, "curse：%f", curse);
	DrawFormatString(0, 170, 0xffffff, "curseLL：%.0f", curseLowerLimit);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d %d", pushB, TRUE);

	patCounter++;
	if (patCounter % 10 == 0)
	{
		patX++;
	}
	if (patX > 3)
	{
		patX = 0;
	}
	if (Hp <= 0)
	{
		DrawBoxAA(x, y, x + IMAGE_SCALE, y + IMAGE_SCALE, GetColor(255, 255, 255), true);
	}
}

void Player::Attack()
{
	if (pushM = Input::IsKeepKeyDown(KEY_INPUT_M))
	{
		MainAttack();
	}
	if (pushB = Input::IsKeepKeyDown(KEY_INPUT_B))
	{
		SubAttack();
	}
}

void Player::Mova()
{
	Stage* s = FindGameObject<Stage>();
	float dt = GetDeltaTime();
	//右に進む
	if (CheckHitKey(KEY_INPUT_D)) {
		//position.x += 3.0f; 加速度を変えて移動していくのでコメントアウト

		islookleft = false;

		if (playerState != JUMP)
		{
			playerState = WALK;
		}

		//徐々に加速していく
		Velocity.x += accel * dt;
		if (Velocity.x > maxSpeed)
		{
			Velocity.x = maxSpeed;
			if (playerState != JUMP)
			{
				playerState = RUN;
			}
		}
	}
	//値がマイナスの時
	//左に進む
	else if (CheckHitKey(KEY_INPUT_A)) {
		//position.x -= 3.0f;

		islookleft = true;

		if (playerState != JUMP)
		{
			playerState = WALK;
		}

		//徐々に加速していく(プラスの処理）
		Velocity.x -= accel * dt;
		if (Velocity.x < -maxSpeed)
		{
			Velocity.x = -maxSpeed;
			if (playerState != JUMP)
			{
				playerState = RUN;
			}
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

		if (playerState != JUMP)
		{
			if (Velocity.x == 0)
			{
				playerState = STAND;
			}
		}
	}
	//位置を変える
	position.x += Velocity.x;

	if (Velocity.x > 0) {
		int d1 = s->HitWallRight((int)(position.x + IMAGE_SCALE - 1), (int)(position.y + IMAGE_SCALE - 1));
		int d2 = s->HitWallRight((int)(position.x + IMAGE_SCALE - 1), (int)(position.y));

		int d = max(d1, d2);
		if (d > 0)
		{
			Velocity.x = 0;
		}

		position.x -= max(d1, d2);
	}
	else if (Velocity.x < 0)
	{
		int d1 = s->HitWallLeft((int)(position.x + 0), (int)(position.y + IMAGE_SCALE - 1));
		int d2 = s->HitWallLeft((int)(position.x + 0), (int)(position.y));

		int d = max(d1, d2);
		if (d > 0)
		{
			Velocity.x = 0;
		}

		position.x += max(d1, d2);
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		jamp();
	}
	//プレイヤー落下
	fall();

	//地面との当たり判定
	if (s != nullptr) {
		int d1 = s->HitFloor((int)(position.x + 0),(int)( position.y + IMAGE_SCALE));
		int d2 = s->HitFloor((int)(position.x + IMAGE_SCALE - 1),(int)( position.y + IMAGE_SCALE));

		int d = max(d1, d2);

		if (d > 0) {
			position.y -= (d - 1);
			Velocity.y = 0;
			CanJump = true;
			if (playerState == JUMP)
			{
				if (Velocity.x == 0)
				{
					playerState = STAND;
				}
				else
				{
					playerState = WALK;
				}
			}
		}
		else {
			CanJump = false;
			playerState = JUMP;
		}
	}
	if (s != nullptr) {
		//天井との当たり判定
		int d1 = s->HitCeiling((int)(position.x + 0), (int)(position.y - 1));//yの方にも＋すると足元が天井判定されるのでなし
		int d2 = s->HitCeiling((int)(position.x + IMAGE_SCALE - 1), (int)(position.y - 1));

		int d = max(d1, d2);

		//天井に触れていないとジャンプをすることが出来ないのでCanJumpをコメントアウト
		if (d > 0) {
			position.y += (d - 1);
			Velocity.y = 0;
		}
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
	//近接（スラッシュ攻撃）
	switch (playerType)
	{
	case(Name1):
		if (pushM == 1)
		{
			PlayerAttack::Player1MainAttack(position, islookleft);
		}
		break;
	case(Name2):
		if (pushM % 10 == 1)
		{
			PlayerAttack::Player2MainAttack(position, islookleft);
		}
		break;
	case(Name3):
		if (pushM == 1)
		{
			PlayerAttack::Player3MainAttack(position, islookleft);
		}
		break;
	default:
		break;
	}
}

void Player::SubAttack()
{
	//遠隔（銃攻撃）
	switch (playerType)
	{
	case (Name1):
		if(curse < (curseMax - cursUpIsPlayer01SubAtttack))
		{
			if (pushB == 1)
			{
				PlayerAttack::Player1SubAttack(position, islookleft);
				UpCurse(cursUpIsPlayer01SubAtttack);
			}
		}
		break;
	case (Name2):
		if (curse < (curseMax - cursUpIsPlayer02SubAtttack))
		{
			if (pushB % 10 == 1)
			{
				PlayerAttack::Player1SubAttack(position, islookleft);
				UpCurse(cursUpIsPlayer02SubAtttack);
			}
		}
		break;
	case(Name3):
		if (curse < (curseMax - cursUpIsPlayer03SubAtttack))
		{
			if (pushB == 1)
			{
				PlayerAttack::Player3SubAttack(position, islookleft);
				UpCurse(cursUpIsPlayer03SubAtttack);
			}
		}
		break;
	default:
		break;
	}
	
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
	position.y += Velocity.y * dt;
	DrawFormatString(30, 80, 0xffffff, "%0.3f", dt);
}

void Player::Interact()
{
	Stage* s = FindGameObject<Stage>();
	//ステージのインタラクト
	canPrevious = s->CanChangeStage(position, "previous");
	canNext = s->CanChangeStage(position, "next");
	IsCorpse = s->IsCorpse(position);
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
		else if (IsCorpse) {
			if (curse - 20 > curseLowerLimit) {
				curse -= 20;
				auto gmmick = FindGameObjects<Gimmick>();
				for (auto gm : gmmick)
				{
					if (gm->GetGimmicType() == GIMMICK_TYPE::Corpse)
					{
						Vector2D gpos = gm->GetPosition();
						Vector2D dist = { abs(gpos.x - position.x),abs(gpos.y - position.y) };
						if (dist.x / IMAGE_SCALE <= 1 && dist.y / IMAGE_SCALE <= 1)
						{
							gm->Destroy();
							break;
						}
					}
				}
			}
			else {
				curse = curseLowerLimit;
			}
		}
	}
}

void Player::Scroll()
{
	// スクロール処理
	if (position.x >= 200) {
		Stage::scrollX = (int)(position.x - 200);
	}

	if (position.y - Stage::scrollY <= 100) {
		Stage::scrollY = (int)(position.y - 100);
	}

	//より自然？なスクロール
	if (position.y - Stage::scrollY >= 150) {
		Stage::scrollY = (int)(position.y - 150);
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
