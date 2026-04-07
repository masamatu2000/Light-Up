#pragma once
#include"Enemy.h"

/// <summary>
/// ”š’e–‚‚ğŠÇ—‚·‚éƒNƒ‰ƒX
/// </summary>
/// <author>H.suginunma</author>

class Bomber : public Enemy
{
public:
	Bomber(const Vector2D& pos);
	~Bomber();
private:
	void Update() override;
	void Draw() override;
	void Move() override;
	void Attack() override;
};

