#include "Gimmick.h"

Gimmick::Gimmick(const Vector2D& pos, const GIMMICK_TYPE& gt)
{
	position = pos;
	gimmicType = gt;
	
}

Gimmick::~Gimmick()
{
}

void Gimmick::Update()
{
	
}


void Gimmick::Draw()
{
	switch (gimmicType) {
	case GIMMICK_TYPE::Corpse:
		DrawBox(position.x - Stage::scrollX, position.y - Stage::scrollY, position.x + IMAGE_SCALE - Stage::scrollX, position.y + IMAGE_SCALE - Stage::scrollY, GetColor(255, 0, 0), TRUE);
		break;
	}
}
