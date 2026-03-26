#pragma once
#include "Stage.h"
#include "GimmickType.h"

class Gimmick : public Object
{
public:
	Gimmick(const Vector2D &pos,const GIMMICK_TYPE&gt);
	~Gimmick();
	GIMMICK_TYPE GetGimmicType() { return gimmicType; }
	Vector2D GetPosition() { return position; }
	void Destroy() { IsDestroy = true; }
private:
	void Update() override;
	void Draw() override;
private:
	GIMMICK_TYPE gimmicType;
	bool IsDestroy;
};