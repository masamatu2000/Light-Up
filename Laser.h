#pragma once
#include"AttackObject.h"
#include<vector>

/// <summary>
/// レーザーを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

struct LaserType {
	float rad;
	float life;
	float offsetX;
	int length;
};

class Laser :public AttackObject {
public:
	Laser(const Vector2D& start, const Vector2D pPos, LaserNumber laserNum, bool lookleft, ObjectTag tag);
	~Laser();
	void Update()override;
	void Draw()override;
	LaserNumber GetLaserNum()
	{
		return laserNumber;
	}
private:
	LaserNumber laserNumber;
	LaserType laserType;
	Vector2D startPos;
	Vector2D endPos;
private:
	//方向により発射位置の調整
	void SetOffsetPosition() override;
	//ライフの計算、識別
	bool CheckNoLife() override;
	//発射位置、当たり判定の設定
	void SetShotPosition(const Vector2D& target);
};