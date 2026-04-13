#include "AttackType.h"
#include "Stage.h"
#include"Player.h"
#include "Laser.h"

/// <summary>
/// レーザーを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

//全体に共通する定数
namespace
{
	//レーザーの構造体定数　　　　サイズ　寿命　位置　長さ
	//敵
	const LaserType TURRET_L = { 20.0f,1.0f,10.0f,1000 }; //タレット
}

//タレット用定数
namespace Turret
{
	//レーザーの色
	const unsigned int COLOR = GetColor(0, 100, 255);
}

Laser::Laser(const Vector2D& start, const Vector2D target, LaserNumber laserNum, bool lookleft, ObjectTag tag)
{
	laserNumber = laserNum;
	position = start;
	islookleft = lookleft;
	objtag = tag;
	switch (laserNum)
	{
	case LaserNumber::TURRET:
		laserType = TURRET_L;
		break;
	}
	//位置を調整
	SetOffsetPosition();
	//位置の設定
	SetShotPosition(target);
}

Laser::~Laser()
{
}

void Laser::Update()
{
	//ライフがないなら処理をしない
	if (CheckNoLife())
	{
		return;
	}
}

void Laser::Draw()
{
	//描画用の変数
	int sX, sY, eX, eY;
	sX = startPos.x - Stage::scrollX;
	sY = startPos.y - Stage::GetScrollY();
	eX = endPos.x - Stage::scrollX;
	eY = endPos.y - Stage::GetScrollY();

	//外側
	DrawLineAA(sX, sY, eX, eY,Turret::COLOR, laserType.rad);
	//内側
	DrawLineAA(sX, sY, eX, eY,GetColor(255, 255, 255), laserType.rad / 2);
}

void Laser::SetOffsetPosition()
{
	//弾をオフセット分移動させる
	//左向いてるなら
	if (islookleft)
	{
		position.x -= laserType.offsetX;
	}
	//右向いてるなら
	else if (!islookleft)
	{
		position.x += laserType.offsetX;
	}
}

bool Laser::CheckNoLife()
{
	float dt = GetDeltaTime();
	if (laserType.life > 0)
	{
		laserType.life -= dt;
		//ライフがないなら弾を消してtrueを返す
		if (laserType.life <= 0)
		{
			DestroyMe();
			return true;
		}
	}
	return false;
}

void Laser::SetShotPosition(const Vector2D& target)
{
	Stage* s = FindGameObject<Stage>();
	//発射位置の設定
	startPos = position;
	//方向ベクトルから終点を計算
	Vector2D dir = Math2D::Normalize(Math2D::Sub(target, startPos));
	endPos = s->CalculateLaserEnd(startPos, dir, laserType.length);

	lineColid = LineColid(startPos, endPos, laserType.rad);
}
