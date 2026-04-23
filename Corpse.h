#pragma once
#include"Gimmick.h"

class Corpse : public Gimmick
{
public:
	Corpse(const Vector2D& pos, const GimmickType& gt, std::string name, int num);
	~Corpse();
	std::string GetCorpseKind() { return corpseKind; }
private:
	void Update() override;
	void Draw() override;
	void fall();
private:
	Vector2D velocity;
	std::string corpseKind; //死体の種類（敵、ボスを判別）
	std::string corpseName; //死体の名前（表示する画像の種類を判別）
};