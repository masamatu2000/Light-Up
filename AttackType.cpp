#include "AttackType.h"
namespace {
	const float BULLET01_SPEED = 100.0f / 60.0f;
	const float BULLET01_RADIUS = 3.0f;
	const float BULLET01_LIFE = 60 * 5;
	const float BULLET02_SPEED = 100.0f / 60.0f;
	const float BULLET02_RADIUS = 3.0f;
	const float BULLET02_LIFE = 60 * 5;
}
Bullet::Bullet(const Vector2D &pos,BULLET_NUMBER bulletNum)
{
	BulletType bt1 = { BULLET01_SPEED,BULLET01_RADIUS ,BULLET01_LIFE};
	BulletType bt2 = { BULLET02_SPEED,BULLET02_RADIUS ,BULLET02_LIFE};
	bullettype[bullet01] = bt1;
	bullettype[bullet02] = bt2;
	bulletNum_ = bulletNum;
	position = pos;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	switch (bulletNum_) {
	case bullet01:
		if (bullettype[bullet01].life > 0) {
			bullettype[bullet01].life--;
			if (bullettype[bullet01].life <= 0) {
				DestroyMe();
				break;
			}
			float dt = GetDeltaTime();
			position.x += bullettype[bullet01].speed * dt;
		}
		break;
	case bullet02:
		if (bullettype[bullet02].life > 0) {
			bullettype[bullet02].life--;
			if (bullettype[bullet02].life <= 0) {
				DestroyMe();
				break;
			}
			float dt = GetDeltaTime();
			position.x += bullettype[bullet01].speed * dt;
		}
		break;
	}
}

void Bullet::Draw()
{
	DrawCircle(position.x, position.y, bullettype[bulletNum_].size, GetColor(255, 255, 255), TRUE);
}
