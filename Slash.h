#pragma once
#include"AttackObject.h"
#include<vector>

/// <summary>
/// スラッシュを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

struct SlashType {
	float vel;
	float rad;
	float life;
	float offsetX;
};

class Slash :public AttackObject
{
public:
	Slash(const Vector2D& pos, SlashNumber slashNum, bool lookleft, ObjectTag tag);//コンストラクタに左を向いているかどうかの処理を追加
	~Slash();
	void Update()override;
	void Draw()override;
	ObjectTag Gettag() { return objtag; }
private:
	SlashNumber slashNum_;
	SlashType slashType;
private:
	//速度計算用の関数
	void CalculateVelocity() override;
	//方向により発射位置の調整
	void SetOffsetPosition() override;
	//ライフの計算、識別
	bool CheckNoLife() override;
};