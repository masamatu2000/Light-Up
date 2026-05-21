#pragma once
#include"Enemy.h"

/// <summary>
/// タレットを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

class Turret : public Enemy
{
public:
	Turret(const Vector2D& pos);
	~Turret();
private:
	void Update() override;
	void Draw() override;
	void Attack() override;
	void ShotLaser();
	//発射位置、当たり判定の設定
	void SetShotPosition(const Vector2D& target);
	void DrawPredictionLine();
private:
	Vector2D startPos;
	Vector2D endPos;
	Vector2D target;
	Coroutine attackCoroutine;
	//攻撃の予測線を表示するか
	bool attackPrediction;
};

