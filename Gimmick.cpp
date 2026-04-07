#include "Gimmick.h"

Gimmick::Gimmick(const Vector2D& pos, const GIMMICK_TYPE& gt)
{
	position = pos;
	gimmicType = gt;
	Velocity = { 0,0 };
	corpseKind = "";
	corpseName = "";
}

Gimmick::Gimmick(const Vector2D& pos, const GIMMICK_TYPE& gt, std::string name, int num)
{
	position = pos;
	gimmicType = gt;
	Velocity = { 0,0 };
	corpseKind = name;
	corpseName = corpseKind + std::to_string(num);
}

Gimmick::~Gimmick()
{
}

void Gimmick::Update()
{
	Stage* s = FindGameObject<Stage>();
	float dt = GetDeltaTime();
	fall();
	int d1 = s->HitFloor((int)(position.x + 0), (int)(position.y + IMAGE_SCALE));
	int d2 = s->HitFloor((int)(position.x + IMAGE_SCALE - 1), (int)(position.y + IMAGE_SCALE));
	int d = max(d1, d2);
	if (d > 0) {
		position.y -= (d - 1);
		Velocity.y = 0;
	}
}


void Gimmick::Draw()
{
	switch (gimmicType) {
	case GIMMICK_TYPE::Corpse:
		DrawBoxAA(position.x - Stage::scrollX, position.y - Stage::GetScrollY(), position.x + IMAGE_SCALE - Stage::scrollX, position.y + IMAGE_SCALE - Stage::GetScrollY(), GetColor(255, 0, 0), TRUE);
		break;
	}
}
void Gimmick::fall() {
	//マイナスの値になっても減速させる、Velocityの値がマイナス　＝　落下
	float dt = GetDeltaTime();
	Velocity.y += GRAVITY * dt;

	//positionを加速度分上昇させる、位置を変える処理
	position.y += Velocity.y*dt;
}