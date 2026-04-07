#pragma once
#include"Enemy.h"

/// <summary>
/// —d¸‚ğŠÇ—‚·‚éƒNƒ‰ƒX
/// </summary>
/// <author>H.suginunma</author>

class Fairy : public Enemy
{
public:
	Fairy(const Vector2D& pos);
	~Fairy();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

