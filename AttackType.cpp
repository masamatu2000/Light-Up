#include "AttackType.h"
#include "Stage.h"
namespace {
	const float BULLET01_SPEED = 100.0f;
	const float BULLET01_RADIUS = 5.0f;
	const float BULLET01_LIFE = 5.0f;
	const float BULLET02_SPEED = 100.0f;
	const float BULLET02_RADIUS = 3.0f;
	const float BULLET02_LIFE = 5.0f;
}
Bullet::Bullet(const Vector2D &pos,BULLET_NUMBER bulletNum)
{
	BulletType bt1 = { BULLET01_SPEED,BULLET01_RADIUS ,BULLET01_LIFE};
	BulletType bt2 = { BULLET02_SPEED,BULLET02_RADIUS ,BULLET02_LIFE};
	bullettype.clear();
	bullettype.push_back(bt1);
	bullettype.push_back(bt2);
	bulletNum_ = bulletNum;
	position = pos;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	float dt = GetDeltaTime();
	switch (bulletNum_) {
	case bullet01:
		if (bullettype[bullet01].life > 0) {
			bullettype[bullet01].life -= dt;
			if (bullettype[bullet01].life <= 0) {
				DestroyMe();
				break;
			}
			position.x += bullettype[bullet01].speed * dt;
		}
		break;
	case bullet02:
		if (bullettype[bullet02].life > 0) {
			bullettype[bullet02].life -= dt;
			if (bullettype[bullet02].life <= 0) {
				DestroyMe();
				break;
			}
			position.x += bullettype[bullet01].speed * dt;
		}
		break;
	}
}

void Bullet::Draw()
{
	float posX = position.x-Stage::scrollX;
	float posY = position.y - Stage::scrollY;
	DrawCircle(posX, posY, bullettype[bulletNum_].size, GetColor(255, 255, 255), TRUE);
}
