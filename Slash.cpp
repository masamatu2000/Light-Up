#include "AttackType.h"
#include "Stage.h"
#include"Player.h"

//全体に共通する定数
namespace
{
	//斬撃の構造体定数				速度　サイズ　寿命　 位置
	//プレイヤー
	const SlashType BASE_S = { 200.0f,  40.0f, 0.1f, 10.0f }; //基本プレイヤー
	const SlashType MAGE_S = { 300.0f,  20.0f, 0.1f, 20.0f }; //メイジ
	const SlashType KNIGHT_S = { 200.0f,  40.0f, 0.1f, 20.0f }; //騎士
	//敵
	const SlashType KURIBOH_S = { 200.0f,  40.0f, 0.1f, 10.0f }; //クリボー
	const SlashType BOMBER_S = { 0.0f,  30.0f, 0.1f,  0.0f }; //爆弾魔
}

Slash::Slash(const Vector2D& pos, SlashNumber slashNum, bool lookleft, ObjectTag tag)
{
	slashNum_ = slashNum;
	position = pos;
	islookleft = lookleft;
	objtag = tag;
	switch (slashNum_) {
	case SlashNumber::BASE:
		slashType = BASE_S;
		break;
	case SlashNumber::MAGE:
		slashType = MAGE_S;
		break;
	case SlashNumber::KNIGHT:
		slashType = KNIGHT_S;
		break;
	case SlashNumber::KURIBOH:
		slashType = KURIBOH_S;
	case SlashNumber::BOMBER:
		slashType = BOMBER_S;
		break;
	}
	//位置を調整
	SetOffsetPosition();
	//向きの設定
	CheckDirection();
	//速度を計算
	CalculateVelocity();
}

Slash::~Slash()
{
}

void Slash::Update()
{
	//ライフがないなら処理をしない
	if (CheckNoLife())
	{
		return;
	}
	//ポジションの更新
	float dt = GetDeltaTime();
	position.x += Velocity.x * dt;
	position.y += Velocity.y * dt;
}

void Slash::Draw()
{
	float posX = position.x - Stage::scrollX;//これでスクロールでも表示されるはず
	float posY = position.y - Stage::GetScrollY();
	DrawCircle(int(posX + 16), int(posY + 16), (int)slashType.rad, GetColor(255, 255, 255), TRUE);

}

void Slash::CalculateVelocity()
{
	Velocity = Math2D::Mul(dir, slashType.vel);
	/*float dt = GetDeltaTime();
	Velocity = Math2D::Mul(Velocity, dt);*/
}

void Slash::SetOffsetPosition()
{
	//弾をオフセット分移動させる
	//左向いてるなら
	if (islookleft)
	{
		position.x -= slashType.offsetX;
	}
	//右向いてるなら
	else if (!islookleft)
	{
		position.x += slashType.offsetX;
	}
	circleColid = CircleColid(Vector2D(0, 0), slashType.rad);
}

bool Slash::CheckNoLife()
{
	float dt = GetDeltaTime();
	if (slashType.life > 0)
	{
		slashType.life -= dt;
		//ライフがないなら弾を消してtrueを返す
		if (slashType.life <= 0)
		{
			DestroyMe();
			return true;
		}
	}
	return false;
}
