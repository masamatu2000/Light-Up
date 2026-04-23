#include "Corpse.h"
#include "Stage.h"

Corpse::Corpse(const Vector2D& pos, const GimmickType& gt, std::string name, int num)
{
	position = pos;
	gimmicType = gt;
	velocity = { 0,0 };
	corpseKind = name;
	corpseName = corpseKind + std::to_string(num);
}

Corpse::~Corpse()
{
}

void Corpse::Update()
{
	Stage* s = FindGameObject<Stage>();
	//落下処理
	fall();
}

void Corpse::Draw()
{
	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::GetScrollY();
	DrawBoxAA(x,y,x + CHARACTER_IMAGE_SCALE,y + CHARACTER_IMAGE_SCALE, GetColor(255, 0, 0), TRUE);
}

void Corpse::fall()
{
	float dt = GetDeltaTime();
	velocity.y += GRAVITY * dt;
	//位置の更新
	position.y += velocity.y * dt;

	float d = CheckHitWall("DOWN");
	if (d > 0)
	{
		position.y -= (d - 1);
		velocity.y = 0;
	}
}
