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
};

