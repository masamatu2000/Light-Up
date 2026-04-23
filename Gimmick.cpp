#include "Gimmick.h"
#include "Stage.h"

Gimmick::Gimmick()
{
	hImage = -1;
}

Gimmick::~Gimmick()
{
}

void Gimmick::Update()
{
}


void Gimmick::Draw()
{
}

float Gimmick::CheckHitWall(std::string wall)
{
	Stage* s = FindGameObject<Stage>();
	if (wall == "RIGHT")
	{
		int d1 = s->HitWallRight(int(position.x + CHARACTER_IMAGE_SCALE - 1), int(position.y + CHARACTER_IMAGE_SCALE - 1));
		int d2 = s->HitWallRight(int(position.x + CHARACTER_IMAGE_SCALE - 1), int(position.y));
		return (float)max(d1, d2);
	}
	else if (wall == "LEFT")
	{
		int d1 = s->HitWallLeft(int(position.x + 0), int(position.y + CHARACTER_IMAGE_SCALE - 1));
		int d2 = s->HitWallLeft(int(position.x + 0), int(position.y));
		return (float)max(d1, d2);
	}
	else if (wall == "DOWN")
	{
		int d1 = s->HitFloor(int(position.x + 0), int(position.y + CHARACTER_IMAGE_SCALE));
		int d2 = s->HitFloor(int(position.x + CHARACTER_IMAGE_SCALE - 1), int(position.y + CHARACTER_IMAGE_SCALE));
		return (float)max(d1, d2);
	}
	else if (wall == "UP")
	{
		int d1 = s->HitCeiling((int)(position.x + 0), (int)(position.y - 1));
		int d2 = s->HitCeiling((int)(position.x + CHARACTER_IMAGE_SCALE - 1), (int)(position.y - 1));
		return (float)max(d1, d2);
	}
	return 0.0f;
}
