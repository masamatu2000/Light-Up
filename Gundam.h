#pragma once
#include"Enemy.h"

/// <summary>
/// クリボーを管理するクラス
/// </summary>
/// <author>H.suginunma</author>

class Gundam : public Enemy
{
public:
	Gundam(const Vector2D& pos);
	~Gundam();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

