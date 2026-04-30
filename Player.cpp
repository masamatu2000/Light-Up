#include "Player.h"
#include "Stage.h"
#include "globals.h"
#include"ImageManager.h"
#include "DataHolder.h"
#include "Enemy.h"
#include"Boss.h"
#include"Gimmick.h"
#include"Corpse.h"
#include"Animation.h"
#include"Bullet.h"
#include"Slash.h"
#include "SoundManager.h"
#include "EffectManager.h"

/// <summary>
/// M.Shoji
/// </summary>
namespace
{
	const float JUMP_HEIGHT = 5.0f*IMAGE_SCALE;
	const float accel = 20.0f;//加速率
	const float decal = 15.0f;//減衰率
	const float maxSpeed = 8.0f;//最高速度

	const float curseMax = 100.0f;
	const float curseDownRatio = 500.0f;
	const float cursUpIsPlayer01SubAtttack = 5.0f;
	const float cursUpIsPlayer02SubAtttack = 1.0f;
	const float cursUpIsPlayer03SubAtttack = 10.0f;
	const float BOX_TIME = 10%60;
	//デバフ関係の定数
	const float PLAYER_SPEED_DEBUFF = 0.5f;
	const float DEBUFF_CURSE_UP = 0.5f;
	const float DEBUFF_TIME = 60*5;
	const int PLAYER_01_MAIN_ATTACK_RECAST_TIME = 20;
	const int PLAYER_02_MAIN_ATTACK_RECAST_TIME = 10;
	const int PLAYER_03_MAIN_ATTACK_RECAST_TIME = 30;
	const int PLAYER_01_SUB_ATTACK_RECAST_TIME = 30;
	const int PLAYER_02_SUB_ATTACK_RECAST_TIME = 10;
	const int PLAYER_03_SUB_ATTACK_RECAST_TIME = 40;
	const int PLAYER_01_SUPPORT_RECAST_TIME = 60;
	const int PLAYER_02_SUPPORT_RECAST_TIME = 60;
	const int PLAYER_03_SUPPORT_RECAST_TIME = 60;
	const int PLAYER_01_RUSH = 5;
	const float PLAYER_01_RUSH_SPEED = IMAGE_SCALE*5;
	const int PLAYER_02_BLINK = 5;
	const float PLAYER_02_BLINK_SPEED = IMAGE_SCALE* 5;

	//カメラの移動する上限値
	const int CAMERA_OFFSET = 60;
	const float CAMERA_MOVE_TIME = 0.1f;

}
Player::Player()
{
	CanJump = true;

	canPrevious = false;
	canNext = false;
	playerType = Name1;

	curse = 0;

	patX = 0;
	patY = 0;
	patCounter = 0;
}

Player::Player(int x, int y)
{
	position = Vector2D((float)x, (float)y);
	Velocity = Vector2D(0.0f,0.0f);
	circleColid = CircleColid(Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2), CHARACTER_IMAGE_SCALE / 2);
	
	CanJump = true;
	canPrevious = false;
	canNext = false;

	curse = 0;
	curseLowerLimit = 0;

	patX = 0;
	patY = 0;
	patCounter = 0;
	Image* image = FindGameObject<Image>();
	hImage = image->ReturnImage("bass");
	DataHolder* dh = FindGameObject<DataHolder>();
	playerType = (PlayerName)(dh->playerNum - 1);
	IsCorpse = false;
	animeState = STAND;
	playState = START;
	isAnimationEnd = false;

	Hp = 1;
	invincibilityTimeCounter = 0;
	coyotejump = false;

	mainAttackRecast = 0;
	subAttackRecast = 0;
	supportRecast = 0;
	isRush = false;
	rushCounter = 0;
	isBlink = false;
	blinkCounter = 0;

	cameraY = 0;

	pushM = 0;
	pushB = 0;
	pushV = 0;

	isDebuff = false;
	isAlreadyDebuff = false;
	DebuffCounter = 0;

	isMaxCurse = false;

}

Player::~Player()
{
}

void Player::Update()
{
	switch (playState)
	{
	case START:
		StartUpdate();
		break;
	case PLAY:
		PlayUpdate();
		break;
	case OVER:
		OverUpdate();
		break;
	case CLEAR:
		ClearUpdate();
		break;
	}
}

void Player::StartUpdate()
{
	playState = PlayState::PLAY;
}

void Player::PlayUpdate()
{
	Move();

	Interact();

	SetCamera();

	Scroll();

	Attack();

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
		isMaxCurse = true;
	}

	if (isDebuff) {
		if (!isAlreadyDebuff) {
			Velocity = { Velocity.x * PLAYER_SPEED_DEBUFF,Velocity.y * PLAYER_SPEED_DEBUFF };
			UpCurse(DEBUFF_CURSE_UP);
			isAlreadyDebuff = true;
		}
		else {
			DebuffCounter++;
			if (DebuffCounter >= DEBUFF_TIME) {
				isDebuff = false;
				isAlreadyDebuff = false;
				DebuffCounter = 0;
			}
		}
	}
	
	//無敵時間の減少
	invincibilityTimeCounter--;
}

void Player::OverUpdate()
{
	SceneManager::ChangeScene(SCENE_NAME::GAMEOVER_SCENE);
}

void Player::ClearUpdate()
{
	if (isAnimationEnd)
	{
		playState = PlayState::START;
		Stage* s = FindGameObject<Stage>();
		s->NextSection();
	}
}

void Player::Draw()
{
	switch (playState)
	{
	case START:
		StartDraw();
		break;
	case PLAY:
		PlayDraw();
		break;
	case OVER:
		OverDraw();
		break;
	}
}

void Player::StartDraw()
{

}

void Player::PlayDraw()
{
	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::GetScrollY();
	if (invincibilityTimeCounter > 0)
	{
		DrawBoxAA(x, y, x + CHARACTER_IMAGE_SCALE, y + CHARACTER_IMAGE_SCALE, GetColor(100, 100, 100), true);
	}
	switch (playerType)
	{
	case(Name1):
		DrawBoxAA(x, y, x + CHARACTER_IMAGE_SCALE, y + CHARACTER_IMAGE_SCALE, GetColor(255, 0, 0), false);
		break;
	case(Name2):
		DrawBoxAA(x, y, x + CHARACTER_IMAGE_SCALE, y + CHARACTER_IMAGE_SCALE, GetColor(0, 255, 0), false);
		break;
	case(Name3):
		DrawBoxAA(x, y, x + CHARACTER_IMAGE_SCALE, y + CHARACTER_IMAGE_SCALE, GetColor(0, 0, 255), false);
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
	switch (animeState)
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
	DrawRectGraph((int)x, (int)y, CHARACTER_IMAGE_SCALE * patX, CHARACTER_IMAGE_SCALE * patY, CHARACTER_IMAGE_SCALE, CHARACTER_IMAGE_SCALE, hImage, TRUE);
	//DrawRectGraph((int)x - IMAGE_SCALE/2, (int)y - IMAGE_SCALE, IMAGE_SCALE * 2 * patX, IMAGE_SCALE * 2 * patY, IMAGE_SCALE * 2, IMAGE_SCALE * 2, hImage, TRUE);

	//DrawFormatString(0, 80, 0xffffff, "次：%d 前：%d", canNext, canPrevious);
	//DrawFormatString(0, 100, 0xffffff, "X：%.0f　Y:%.0f",x,y);
	DrawFormatString(0, 150, 0xffffff, "M：%d S：%d SP: %d", mainAttackRecast, subAttackRecast,supportRecast);
	//DrawFormatString(0, 100, 0xffffff, "X：%.0f　Y:%.0f", x, y);
	//DrawFormatString(0, 150, 0xffffff, "M：%d S：%d", mainAttackRecast, subAttackRecast);

	/*DrawFormatString(0, 250, 0xffffff, "curse：%f", curse);
	DrawFormatString(0, 270, 0xffffff, "curseLL：%.0f", curseLowerLimit);*/
	DrawFormatString(0, 180, 0xffffff, "%.0f", cameraY);

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
		//playState = OVER;
		DrawBoxAA(x, y, x + CHARACTER_IMAGE_SCALE, y + CHARACTER_IMAGE_SCALE, GetColor(255, 255, 255), true);
	}
}

void Player::OverDraw()
{
}

void Player::ClearDraw()
{
}

void Player::Attack()
{
	if (((pushM = Input::IsKeepKeyDown(KEY_INPUT_M)) || (pushM = Input::IsKeepPadDown(Pad::X))) && mainAttackRecast <= 0)
	{
		MainAttack();
	}
	if (((pushB = Input::IsKeepKeyDown(KEY_INPUT_B)) || (pushB =  Input::IsKeepPadDown(Pad::B))) && subAttackRecast <= 0)
	{
		SubAttack();
	}
	if (((pushV = Input::IsKeepKeyDown(KEY_INPUT_V)) || (pushV = Input::IsKeepPadDown(Pad::Y))) && supportRecast <= 0)
	{
		SupportSkill();
	}
	mainAttackRecast--;
	subAttackRecast--;
	supportRecast--;
	if (mainAttackRecast < 0)
	{
		mainAttackRecast = 0;
	}
	if (subAttackRecast < 0)
	{
		subAttackRecast = 0;
	}
	if (supportRecast < 0) {
		supportRecast = 0;
	}
}

void Player::Move()
{
	Stage* s = FindGameObject<Stage>();
	float dt = GetDeltaTime();
	//右に進む
	if (isRush) {
		
		if (islookleft) {
			float dx = PLAYER_01_RUSH_SPEED * (60.0f / PLAYER_01_RUSH) * dt;
			float step = dx / 10.0f;

			for (float moved = 0; moved <= dx; moved += step) {
				float nextX = position.x - moved;

				int d1 = s->HitWallLeft((int)(nextX), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
				int d2 = s->HitWallLeft((int)(nextX), (int)(position.y));

				if (max(d1, d2) > 0) {
					dx = moved - step; // 壁の手前で止める
					break;
				}
			}

			position.x -= dx;
		}
		else {
			float dx = PLAYER_01_RUSH_SPEED * (60.0f / PLAYER_01_RUSH) * dt;
			float step = dx / 10.0f;

			for (float moved = 0; moved <= dx; moved += step) {
				float nextX = position.x + moved;

				int d1 = s->HitWallRight((int)(nextX + CHARACTER_IMAGE_SCALE), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
				int d2 = s->HitWallRight((int)(nextX + CHARACTER_IMAGE_SCALE), (int)(position.y));

				if (max(d1, d2) > 0) {
					dx = moved - step;
					break;
				}
			}

			position.x += dx;
		}

		rushCounter++;
		if (rushCounter > PLAYER_01_RUSH) {
			isRush = false;
			rushCounter = 0;
		}
	}
	else if (isBlink) {
	
		if (islookleft) {
			float dx = PLAYER_02_BLINK_SPEED * (60.0f / PLAYER_02_BLINK) * dt;
			float step = dx / 10.0f;
			for (float moved = 0; moved <= dx; moved += step) {
				float nextX = position.x - moved;

				int d1 = s->HitWallLeft((int)(nextX), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
				int d2 = s->HitWallLeft((int)(nextX), (int)(position.y));

				if (max(d1, d2) > 0) {
					dx = moved - step; // 壁の手前で止める
					break;
				}
			}
			position.x -= dx;
		}
		else {
			float dx = PLAYER_02_BLINK_SPEED * (60.0f / PLAYER_02_BLINK) * dt;
			float step = dx / 10.0f;

			for (float moved = 0; moved <= dx; moved += step) {
				float nextX = position.x + moved;

				int d1 = s->HitWallRight((int)(nextX + CHARACTER_IMAGE_SCALE), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
				int d2 = s->HitWallRight((int)(nextX + CHARACTER_IMAGE_SCALE), (int)(position.y));

				if (max(d1, d2) > 0) {
					dx = moved - step;
					break;
				}
			}

			position.x += dx;
		}
		blinkCounter++;
		if (blinkCounter > PLAYER_02_BLINK) {
			isBlink = false;
			blinkCounter = 0;
		}
	}
	else {
		if (CheckHitKey(KEY_INPUT_D) || Input::IsKeepPadDown(Pad::RIGHT)) {
			//position.x += 3.0f; 加速度を変えて移動していくのでコメントアウト

			islookleft = false;

			if (animeState != JUMP)
			{
				animeState = WALK;
			}

			//徐々に加速していく
			Velocity.x += accel * dt;
			if (Velocity.x > maxSpeed)
			{
				Velocity.x = maxSpeed;
				if (animeState != JUMP)
				{
					animeState = RUN;
				}
			}
		}
		//値がマイナスの時
		//左に進む
		else if (CheckHitKey(KEY_INPUT_A) || Input::IsKeepPadDown(Pad::LEFT)) {
			//position.x -= 3.0f;

			islookleft = true;

			if (animeState != JUMP)
			{
				animeState = WALK;
			}

			//徐々に加速していく(プラスの処理）
			Velocity.x -= accel * dt;
			if (Velocity.x < -maxSpeed)
			{
				Velocity.x = -maxSpeed;
				if (animeState != JUMP)
				{
					animeState = RUN;
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

			if (animeState != JUMP)
			{
				if (Velocity.x == 0)
				{
					animeState = STAND;
				}
			}
		}
		//位置を変える
		position.x += Velocity.x;

		if (Velocity.x > 0) {
			int d1 = s->HitWallRight((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
			int d2 = s->HitWallRight((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y + CHARACTER_IMAGE_SCALE / 2));
			int d3 = s->HitWallRight((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y));

			int d = max(max(d1, d2), d3);
			if (d > 0)
			{
				Velocity.x = 0;
			}

			position.x -= d;
		}
		else if (Velocity.x < 0)
		{
			int d1 = s->HitWallLeft((int)(position.x + 0), (int)(position.y + CHARACTER_IMAGE_SCALE - 1));
			int d2 = s->HitWallLeft((int)(position.x + 0), (int)(position.y + CHARACTER_IMAGE_SCALE / 2));
			int d3 = s->HitWallLeft((int)(position.x + 0), (int)(position.y));

			int d = max(max(d1, d2), d3);
			if (d > 0)
			{
				Velocity.x = 0;
			}

			position.x += d;
		}

		if (Input::IsKeepKeyDown(KEY_INPUT_SPACE) || Input::IsKeepPadDown(Pad::A)) {
			jamp();
		}
		//プレイヤー落下
		fall();

		//地面との当たり判定
		if (s != nullptr) {
			int d1 = s->HitFloor((int)(position.x + 0), (int)(position.y + CHARACTER_IMAGE_SCALE));
			int d2 = s->HitFloor((int)(position.x + CHARACTER_IMAGE_SCALE / 2), (int)(position.y + CHARACTER_IMAGE_SCALE));
			int d3 = s->HitFloor((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y + CHARACTER_IMAGE_SCALE));

			int d = max(max(d1, d2), d3);
			static float timer = 0;

			if (d > 0) {
				position.y -= (d - 1);
				Velocity.y = 0;
				CanJump = true;
				timer = 0;
				if (animeState == JUMP)
				{
					if (Velocity.x == 0)
					{
						animeState = STAND;
					}
					else
					{
						animeState = WALK;
					}
				}
			}
			else {
				timer++;
				if (timer < BOX_TIME && Velocity.y > 0) {
					CanJump = true;
				}
				else {
					CanJump = false;
					animeState = JUMP;
				}
			}
		}
		if (s != nullptr) {
			//天井との当たり判定
			int d1 = s->HitCeiling((int)(position.x + 0), (int)(position.y - 1));//yの方にも＋すると足元が天井判定されるのでなし
			int d2 = s->HitCeiling((int)(position.x + CHARACTER_IMAGE_SCALE / 2), (int)(position.y - 1));
			int d3 = s->HitCeiling((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y - 1));

			int d = max(max(d1, d2), d3);

			//天井に触れていないとジャンプをすることが出来ないのでCanJumpをコメントアウト
			if (d > 0) {
				position.y += (d - 1);
				Velocity.y = 0;
			}
		}
	}
}

void Player::jamp()
{

	if (CanJump){
		//初期速度の設定
		float InitialVelocity = -std::sqrt(2.0f * GRAVITY * JUMP_HEIGHT);
		Velocity.y = InitialVelocity;//dtは正の値でジャンプさせるには負の値にする必要あり
		CanJump = false;
	}

}


void Player::MainAttack()
{
	//近接（スラッシュ攻撃）
	Vector2D Apos = Math2D::Add(position, Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2));
	switch (playerType)
	{
	case(Name1):
		if (pushM == 1)
		{
			new Slash(Apos, SlashNumber::BASE, islookleft, ObjectTag::PLAYER);
			new Effect(Apos.x,Apos.y);
			mainAttackRecast = PLAYER_01_MAIN_ATTACK_RECAST_TIME;
			
			FindGameObject<Sound>()->EffectSoundPlay("slash");
		}

		break;
	case(Name2):
		new Slash(Apos, SlashNumber::MAGE, islookleft, ObjectTag::PLAYER);
		mainAttackRecast = PLAYER_02_MAIN_ATTACK_RECAST_TIME;
		break;
	case(Name3):
		if (pushM == 1)
		{
			new Slash(Apos, SlashNumber::KNIGHT, islookleft, ObjectTag::PLAYER);
			mainAttackRecast = PLAYER_03_MAIN_ATTACK_RECAST_TIME;
		}
		break;
	default:
		break;
	}
}

void Player::SubAttack()
{
	//遠隔（銃攻撃）
	Vector2D Apos = Math2D::Add(position, Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2));
	switch (playerType)
	{
	case (Name1):
		if(curse < (curseMax - cursUpIsPlayer01SubAtttack))
		{
			if (pushB == 1)
			{
				new Bullet(Apos, BulletNumber::BASE, islookleft, ObjectTag::PLAYER);
				UpCurse(cursUpIsPlayer01SubAtttack);
			}
			subAttackRecast = PLAYER_01_SUB_ATTACK_RECAST_TIME;
		}
		break;
	case (Name2):
		if (curse < (curseMax - cursUpIsPlayer02SubAtttack))
		{
			new Bullet(Apos, BulletNumber::MAGE, islookleft, ObjectTag::PLAYER);
			UpCurse(cursUpIsPlayer02SubAtttack);
			subAttackRecast = PLAYER_02_SUB_ATTACK_RECAST_TIME;
		}
		break;
	case(Name3):
		if (curse < (curseMax - cursUpIsPlayer03SubAtttack))
		{
			if (pushB == 1)
			{
				new Slash(Apos, SlashNumber::KNIGHT, islookleft, ObjectTag::PLAYER);
				new Bullet(Apos, BulletNumber::KNIGHT, islookleft, ObjectTag::PLAYER);
				UpCurse(cursUpIsPlayer03SubAtttack);
			}
			subAttackRecast = PLAYER_03_SUB_ATTACK_RECAST_TIME;
		}
		break;
	default:
		break;
	}
	
}

void Player::SupportSkill()
{
	Stage* s = FindGameObject<Stage>();
	switch (playerType)
	{
	case (Name1):
		isRush = true;
		supportRecast = PLAYER_01_SUPPORT_RECAST_TIME;
		break;
	case (Name2):
		isBlink = true;
		SetInvincibilityTime();
		supportRecast = PLAYER_02_SUPPORT_RECAST_TIME;
		break;
	case(Name3):
		//ガード
		supportRecast = PLAYER_03_SUPPORT_RECAST_TIME;
		break;
	default:
		break;
	}
}

void Player::fall()
{
	//マイナスの値になっても減速させる、Velocityの値がマイナス　＝　落下
	float dt = GetDeltaTime();
	Velocity.y += GRAVITY * dt;

	//positionを加速度分上昇させる、位置を変える処理
	position.y += Velocity.y * dt;
	//DrawFormatString(30, 80, 0xffffff, "dt:%0.3f", dt);
}

void Player::SetCamera()
{
	static float timer = 0;
	static float startY = 0;
	//前回の目的地を保存
	static int lastOffsetY = 0;
	int offsetY = 0;

	bool isPressDown = Input::IsKeepKeyDown(KEY_INPUT_S) ||
		(Input::IsKeepPadDown(Pad::DOWN) && (Input::IsKeepPadDown(Pad::LEFT) == 0 && Input::IsKeepPadDown(Pad::RIGHT) == 0));
	
	if (isPressDown)
	{
		offsetY = CAMERA_OFFSET;

		if (offsetY + Stage::scrollY > Stage::mapBottom)
		{
			offsetY = Stage::mapBottom - Stage::scrollY;
		}
	}

	//地面にいてかつ、目的地が変わった時に初期化
	if (CanJump)
	{
		if (offsetY != lastOffsetY)
		{
			startY = cameraY;
			timer = 0.0f;
			lastOffsetY = offsetY;
		}
	}


	//カメラの移動
	float dt = GetDeltaTime();
	timer += dt;
	if (timer > CAMERA_MOVE_TIME)
	{
		timer = CAMERA_MOVE_TIME;
	}
	float rate = timer / CAMERA_MOVE_TIME;

	cameraY = startY + (lastOffsetY - startY) * rate;
}

void Player::Interact()
{
	Stage* s = FindGameObject<Stage>();
	//ステージのインタラクト
	canPrevious = s->CanChangeStage(position, "previous");
	canNext = s->CanChangeStage(position, "next");
	if (Input::IsKeyDown(KEY_INPUT_E) || Input::IsPadDown(Pad::UP))
	{
		if (canNext)
		{
			s->NextSection();
		}
		else if (canPrevious)
		{
			s->PreviousSection();
		}
		else
		{
			CorpseInteract();
		}
	}
}

void Player::CorpseInteract()
{
	auto corpse = FindGameObjects<Corpse>();
	for (auto cp : corpse)
	{
		
		Vector2D cpos = cp->GetPosition();
		float dist = Math2D::Length(Math2D::Sub(cpos, position));
		if (dist <= IMAGE_SCALE && cp->GetCorpseKind() == "Enemy")
		{
			CurseRecovery();
			cp->DestroyMe();
			break;
		}
		else if (dist <= IMAGE_SCALE && cp->GetCorpseKind() == "Boss")
		{
			ClearAnimation();
			playState = PlayState::CLEAR;
		}
	}
}

void Player::CurseRecovery()
{
	curse -= 20;
	if (curseLowerLimit > curse)
	{
		curse = curseLowerLimit;
	}

}

void Player::ClearAnimation()
{
	new Animation(Name::CLEAR);
}

void Player::AnimationEnd()
{
	isAnimationEnd = true;
}

void Player::Scroll()
{
	// スクロール処理
	if (position.x >= (WIN_WIDTH / SCREEN_ZOOM) / 2) {
		Stage::scrollX = (int)(position.x - (WIN_WIDTH / SCREEN_ZOOM) / 2);
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

