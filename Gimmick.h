#pragma once
#include "Stage.h"
#include "GimmickType.h"

class Gimmick : public Object
{
public:
	Gimmick(const Vector2D &pos,const GIMMICK_TYPE&gt);
	Gimmick(const Vector2D& pos, const GIMMICK_TYPE& gt, std::string name, int num);
	~Gimmick();
	GIMMICK_TYPE GetGimmicType() { return gimmicType; }
	Vector2D GetPosition() { return position; }
	void fall();
	std::string GetCorpseKind() { return corpseKind; }
private:
	void Update() override;
	void Draw() override;
private:
	GIMMICK_TYPE gimmicType;
	Vector2D Velocity;
	std::string corpseKind; //死体の種類（敵、ボスを判別）
	std::string corpseName; //死体の名前（表示する画像の種類を判別）
};