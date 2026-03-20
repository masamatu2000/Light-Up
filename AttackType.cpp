#include "AttackType.h"
#include "Stage.h"
namespace {
	const float BULLET01_SPEED = 100.0f;
	const float BULLET01_RADIUS = 5.0f;
	const float BULLET01_LIFE = 5.0f;
	const float BULLET02_SPEED = 100.0f;
	const float BULLET02_RADIUS = 3.0f;
	const float BULLET02_LIFE = 5.0f;
	const float SLASH01_SPEED = 200.0f;
	const float SLASH01_RADIUS = 10.0f;
	const float SLASH01_LIFE = 0.1f;
	const float SLASH02_SPEED = 200.0f;
	const float SLASH02_RADIUS = 10.0f;
	const float SLASH02_LIFE = 0.1f;
}
Bullet::Bullet(const Vector2D &pos,BULLET_NUMBER bulletNum)
{
	BulletType bt1 = { BULLET01_SPEED,BULLET01_RADIUS ,BULLET01_LIFE};
	BulletType bt2 = { BULLET02_SPEED,BULLET02_RADIUS ,BULLET02_LIFE};
	BulletType2 bt3 = { BULLET01_SPEED,BULLET01_RADIUS ,BULLET01_LIFE };
	BulletType2 bt4 = { BULLET02_SPEED,BULLET02_RADIUS ,BULLET02_LIFE };
	BulletType3 bt5 = { BULLET01_SPEED,BULLET01_RADIUS ,BULLET01_LIFE };
	BulletType3 bt6 = { BULLET02_SPEED,BULLET02_RADIUS ,BULLET02_LIFE };
	bullettype.clear();
	bullettype.push_back(bt1);
	bullettype.push_back(bt2);
	bullettype2.push_back(bt3);
	bullettype2.push_back(bt4);
	bullettype3.push_back(bt5);
	bullettype3.push_back(bt6);
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
			if (bullettype[bullet01].life < 0) {
				DestroyMe();
				break;
			}
			position.x += bullettype[bullet01].speed * dt;
		}
		break;
	case bullet02:
		if (bullettype[bullet02].life > 0) {
			bullettype[bullet02].life -= dt;
			if (bullettype[bullet02].life < 0) {
				DestroyMe();
				break;
			}
			position.x += bullettype[bullet02].speed * dt;
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

Slash::Slash(const Vector2D& pos, SLASH_NUMBER slashNum)
{
	SlashType s1 = { SLASH01_SPEED,SLASH01_RADIUS,SLASH01_LIFE };
	SlashType s2 = { SLASH02_SPEED,SLASH02_RADIUS,SLASH02_LIFE };
	SlashType2 s3 = { SLASH01_SPEED,SLASH01_RADIUS,SLASH01_LIFE };
	SlashType2 s4 = { SLASH02_SPEED,SLASH02_RADIUS,SLASH02_LIFE };
	SlashType3 s5 = { SLASH01_SPEED,SLASH01_RADIUS,SLASH01_LIFE };
	SlashType3 s6 = { SLASH02_SPEED,SLASH02_RADIUS,SLASH02_LIFE };
	slashtype.clear();
	slashtype.push_back(s1);
	slashtype.push_back(s2);
	slashtype2.push_back(s3);
	slashtype2.push_back(s4);
	slashtype3.push_back(s5);
	slashtype3.push_back(s6);
	slashNum_ = slashNum;
	position = pos;

}

Slash::~Slash()
{
}

void Slash::Update()
{
	float dt = GetDeltaTime();
	switch (slashNum_){
		//斬撃によってモーション変化（これはもしかしたら複数ないかもだが）
	case slash01:
		if (slashtype[slash01].life > 0){
			slashtype[slash01].life -= dt;//斬撃の表示されている時間を減らす
			if (slashtype[slash01].life < 0){
				DestroyMe();
				break;
			}
			position.x += slashtype[slash01].speed * dt;//時間まで前に進む
		}
		break;
	case slash02:
		if (slashtype[slash02].life > 0) {
			slashtype[slash02].life -= dt;
			if (slashtype[slash02].life < 0) {
				DestroyMe();
				break;
			}
			position.x += slashtype[slash01].speed * dt;
		}
		break;
	}
}

void Slash::Draw()
{
	float posX = position.x - Stage::scrollX;//これでスクロールでも表示されるはず
	float posY = position.y - Stage::scrollY;
	DrawCircle(posX, posY, slashtype[slashNum_].size, GetColor(255, 255, 255),TRUE);

}
