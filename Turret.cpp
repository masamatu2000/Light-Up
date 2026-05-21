#include "Turret.h"
#include"Player.h"
#include"Stage.h"
#include"Gimmick.h"
#include"Laser.h"

/// <summary>
/// タレットを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

//タレット用の定数
namespace TurretData
{
	//タレットの継続時間
	const float SHOT_TIME = 1.0f;
	//レーザーの長さ
	const float LASER_LENGTH = 1000.0f;
	//レーザーの太さ
	const float LASER_SIZE = 20.0f;
}

Turret::Turret(const Vector2D& pos)
{
	position = pos;
	timer = 0.0f;
	invincibilityTimeCounter = 0;
	enemyNumber = EnemyNumber::TURRET;
	enemyStatus = GetEnemyStatus(enemyNumber);
	Image* image = FindGameObject<Image>();
	hImage = image->ReturnImage(enemyStatus.imageName);
	SetStatus();
}

Turret::~Turret()
{
}

void Turret::Update()
{
	Enemy::Update();
	attackCoroutine.Update();
	Attack();
}

void Turret::Draw()
{
	Object::Draw();
	Enemy::Draw();
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::GetScrollY();
	DrawRectGraph((int)positionx, (int)positiony, CHARACTER_IMAGE_SCALE * 0, CHARACTER_IMAGE_SCALE * 0, CHARACTER_IMAGE_SCALE, CHARACTER_IMAGE_SCALE, hImage, TRUE);
	if (attackPrediction)
	{
		DrawPredictionLine();
	}
}

void Turret::Attack()
{
	if (!gGameTimer.IsEvery(enemyStatus.coolTime))return;

	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	//狙撃対象の位置
	target = { pPos.x + CHARACTER_IMAGE_SCALE / 2.0f , pPos.y + CHARACTER_IMAGE_SCALE / 2.0f };
	SetShotPosition(target);
	//プレイヤーとの距離
	float distance = Math2D::Length(Math2D::Sub(target, startPos));
	attackPrediction = true;

	//距離が一定以下かつ、クールタイムが終わっているなら攻撃可能に
	if (distance <= enemyStatus.attackDistance)
	{
		attackCoroutine.Start([this] {ShotLaser(); }, 1.0f);
	}
}

void Turret::ShotLaser()
{
	new Laser(startPos, endPos, LaserNumber::TURRET, false, ObjectTag::ENEMY);
	attackPrediction = false;
}

void Turret::SetShotPosition(const Vector2D& target)
{
	Stage* s = FindGameObject<Stage>();
	//発射位置の設定
	startPos = Math2D::Add(position, Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2));
	//方向ベクトルから終点を計算
	Vector2D dir = Math2D::Normalize(Math2D::Sub(target, startPos));
	endPos = s->CalculateLaserEnd(startPos, dir, TurretData::LASER_LENGTH);

	//lineColid = LineColid(startPos, endPos, TurretData::LASER_SIZE);
}

void Turret::DrawPredictionLine()
{
	//描画用の変数
	float sX, sY, eX, eY;
	sX = startPos.x - Stage::scrollX;
	sY = startPos.y - Stage::GetScrollY();
	eX = endPos.x - Stage::scrollX;
	eY = endPos.y - Stage::GetScrollY();

	//予測線本体
	DrawLineAA(sX, sY, eX, eY,GetColor(255,0,0));
}
