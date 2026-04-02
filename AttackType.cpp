#include "AttackType.h"
#include "Stage.h"
#include"Player.h"
/// <summary>
/// プレイヤーの攻撃方法を管理する
/// M.Shoji
/// </summary>

namespace {
	const float BULLET01_SPEED = 300.0f;
	const float BULLET01_RADIUS = 15.0f;
	const float BULLET01_LIFE = 3.0f;
	const float BULLET01_POS = 10.0f;
	const float BULLET02_SPEED = 500.0f;
	const float BULLET02_RADIUS = 2.0f;
	const float BULLET02_LIFE = 3.0f;
	const float BULLET02_POS = 10.0f;
	const float BULLET03_SPEED = 100.0f;
	const float BULLET03_RADIUS = 20.0f;
	const float BULLET03_LIFE = 3.0f;
	const float BULLET03_POS = 20.0f;
	const float BULLET04_SPEED = 300.0f;
	const float BULLET04_RADIUS = 10.0f;
	const float BULLET04_LIFE = 3.0f;
	const float BULLET04_POS = 10.0f;
	const float BULLET05_SPEED = 300.0f;
	const float BULLET05_RADIUS = 10.0f;
	const float BULLET05_LIFE = 7.0f;
	const float BULLET05_POS = 10.0f;

	const float SLASH01_SPEED = 200.0f;
	const float SLASH01_RADIUS = 40.0f;
	const float SLASH01_LIFE = 0.1f;
	const float SLASH01_POS = 10.0f;
	const float SLASH02_SPEED = 300.0f;
	const float SLASH02_RADIUS = 20.0f;
	const float SLASH02_LIFE = 0.1f;
	const float SLASH02_POS = 20.0f;
	const float SLASH03_SPEED = 200.0f;
	const float SLASH03_RADIUS = 40.0f;
	const float SLASH03_LIFE = 0.1f;
	const float SLASH03_POS = 20.0f;

}

Bullet::Bullet(const Vector2D &pos,BULLET_NUMBER bulletNum,bool lookleft,OBJECT_TAG tag)
{
	BulletType bt1 = { BULLET01_SPEED,BULLET01_RADIUS,BULLET01_LIFE };
	BulletType bt2 = { BULLET02_SPEED,BULLET02_RADIUS,BULLET02_LIFE };
	BulletType bt3 = { BULLET03_SPEED,BULLET03_RADIUS,BULLET03_LIFE };
	BulletType bt4 = { BULLET04_SPEED,BULLET04_RADIUS,BULLET04_LIFE };
	BulletType bt5 = { BULLET05_SPEED,BULLET05_RADIUS,BULLET05_LIFE };
	bullettype.clear();
	bullettype.push_back(bt1);
	bullettype.push_back(bt2);
	bullettype.push_back(bt3);
	bullettype.push_back(bt4);
	bullettype.push_back(bt5);
	bulletNum_ = bulletNum;
	position = pos;
	islookleft = lookleft;
	switch (bulletNum_) {
	case bullet01:
		if (islookleft == false)
		{
			position = Math2D::Add(pos, Vector2D(BULLET01_POS, 0.0f));
		}
		else
		{
			position = Math2D::Sub(pos, Vector2D(BULLET01_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), BULLET01_RADIUS);
		break;
	case bullet02:
		if (islookleft == false)
		{
			position = Math2D::Add(pos, Vector2D(BULLET02_POS, 0.0f));
		}
		else
		{
			position = Math2D::Sub(pos, Vector2D(BULLET02_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), BULLET02_RADIUS);
		break;
	case bullet03:
		if (islookleft == false)
		{
			position = Math2D::Add(pos, Vector2D(BULLET03_POS, 0.0f));
		}
		else
		{
			position = Math2D::Sub(pos, Vector2D(BULLET03_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), BULLET03_RADIUS);
		break;
	case bullet04:
		if (islookleft == false)
		{
			position = Math2D::Add(pos, Vector2D(BULLET04_POS, 0.0f));
		}
		else
		{
			position = Math2D::Sub(pos, Vector2D(BULLET04_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), BULLET04_RADIUS);
		break;
	case TURRET_BULLET:
		if (islookleft == false)
		{
			position = Math2D::Add(pos, Vector2D(BULLET05_POS, 0.0f));
		}
		else
		{
			position = Math2D::Sub(pos, Vector2D(BULLET05_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), BULLET05_RADIUS);
		break;
	}
	objtag = tag;
	/*Player* pl = FindGameObject<Player>();
	Vector2D distance= Math2D::Sub(pl->GetPosition(), position);
	dir = Math2D::Normalize(distance);*/
}

Bullet::Bullet(const Vector2D& pos, BULLET_NUMBER bulletNum, Vector2D direction, OBJECT_TAG tag)
{
	dir = direction;
	BulletType bt1 = { BULLET01_SPEED,BULLET01_RADIUS,BULLET01_LIFE };
	BulletType bt2 = { BULLET02_SPEED,BULLET02_RADIUS,BULLET02_LIFE };
	BulletType bt3 = { BULLET03_SPEED,BULLET03_RADIUS,BULLET03_LIFE };
	BulletType bt4 = { BULLET04_SPEED,BULLET04_RADIUS,BULLET04_LIFE };
	BulletType bt5 = { BULLET05_SPEED,BULLET05_RADIUS,BULLET05_LIFE };
	bullettype.clear();
	bullettype.push_back(bt1);
	bullettype.push_back(bt2);
	bullettype.push_back(bt3);
	bullettype.push_back(bt4);
	bullettype.push_back(bt5);
	bulletNum_ = bulletNum;
	position = pos;
	objtag = tag;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	float dt = GetDeltaTime();
	Stage* s = FindGameObject<Stage>();
	switch (bulletNum_) {
	case bullet01:
		if (bullettype[bullet01].life > 0)
		{
			bullettype[bullet01].life -= dt;
			if (bullettype[bullet01].life <= 0) 
			{
				DestroyMe();
				break;
			}
			//どちらを向いているか確認して前に発射する
			if (islookleft == true) 
			{
				position.x -= bullettype[bullet01].speed * dt;
			}
			else 
			{
				position.x += bullettype[bullet01].speed * dt;
			}
		}
		break;
	case bullet02:
		if (bullettype[bullet02].life > 0)
		{
			bullettype[bullet02].life -= dt;
			if (bullettype[bullet02].life <= 0)
			{
				DestroyMe();
				break;
			}
			if (islookleft == true)
			{
				position.x -= bullettype[bullet02].speed * dt;

			}
			else
			{
				position.x += bullettype[bullet02].speed * dt;

			}
		}
		break;
	case bullet03:
		if (bullettype[bullet03].life > 0)
		{
			bullettype[bullet03].life -= dt;
			if (bullettype[bullet03].life <= 0) 
			{
				DestroyMe();
				break;
			}
			if (islookleft == true) 
			{
				position.x -= bullettype[bullet03].speed * dt;
			}
			else 
			{
				position.x += bullettype[bullet03].speed * dt;
			}
		}
		break;
	case bullet04:
		if (bullettype[bullet04].life > 0)
		{
			bullettype[bullet04].life -= dt;
			if (bullettype[bullet04].life <= 0)
			{
				DestroyMe();
				break;
			}
				position.x += bullettype[bullet04].speed *dir.x* dt;
				position.y+= bullettype[bullet04].speed * dir.y * dt;
		}
	case TURRET_BULLET:
		if (bullettype[TURRET_BULLET].life > 0)
		{
			bullettype[TURRET_BULLET].life -= dt;
			if (bullettype[TURRET_BULLET].life <= 0)
			{
				DestroyMe();
				break;
			}
			position.x += bullettype[TURRET_BULLET].speed * dir.x * dt;
			position.y += bullettype[TURRET_BULLET].speed * dir.y * dt;
		}
		break;
	}
	int d1 = s->HitWallRight((int)(position.x + IMAGE_SCALE - 1), (int)(position.y + IMAGE_SCALE - 1));
	int d2 = s->HitWallRight((int)(position.x + IMAGE_SCALE - 1), (int)(position.y));

	int da = max(d1, d2);
	if (da > 0)
	{
		DestroyMe();
	}
	int d3 = s->HitWallLeft((int)(position.x + 0), (int)(position.y + IMAGE_SCALE - 1));
	int d4 = s->HitWallLeft((int)(position.x + 0), (int)(position.y));

	int db = max(d3, d4);
	if (db > 0)
	{
		DestroyMe();
	}
}

void Bullet::Draw()
{
	float posX = position.x-Stage::scrollX;
	float posY = position.y - Stage::scrollY;
	DrawCircle((int)posX+16,(int) posY+16,(int) bullettype[bulletNum_].size, GetColor(255, 255, 255), TRUE);
}

Slash::Slash(const Vector2D& pos, SLASH_NUMBER slashNum,bool lookleft,OBJECT_TAG tag)
{
	SlashType s1 = { SLASH01_SPEED,SLASH01_RADIUS,SLASH01_LIFE };
	SlashType s2 = { SLASH02_SPEED,SLASH02_RADIUS,SLASH02_LIFE };
	SlashType s3 = { SLASH03_SPEED,SLASH03_RADIUS,SLASH03_LIFE };
	SlashType2 s4 = { SLASH01_SPEED,SLASH01_RADIUS,SLASH01_LIFE };
	SlashType2 s5 = { SLASH02_SPEED,SLASH02_RADIUS,SLASH02_LIFE };
	SlashType2 s6 = { SLASH03_SPEED,SLASH03_RADIUS,SLASH03_LIFE };
	SlashType3 s7 = { SLASH01_SPEED,SLASH01_RADIUS,SLASH01_LIFE };
	SlashType3 s8 = { SLASH02_SPEED,SLASH02_RADIUS,SLASH02_LIFE };
	SlashType3 s9 = { SLASH03_SPEED,SLASH03_RADIUS,SLASH03_LIFE };
	slashtype.clear();
	slashtype.push_back(s1);
	slashtype.push_back(s2);
	slashtype.push_back(s3);
	slashtype2.push_back(s4);
	slashtype2.push_back(s5);
	slashtype2.push_back(s6);
	slashtype3.push_back(s7);
	slashtype3.push_back(s8);
	slashtype3.push_back(s9);
	slashNum_ = slashNum;
	islookleft = lookleft;
	//斬撃の出現位置の指定
	switch (slashNum_) {
	case slash01:
		if (islookleft == false)
		{
			position = Math2D::Add(pos, Vector2D(SLASH01_POS, 0.0f));
		}
		else 
		{
			position = Math2D::Sub(pos, Vector2D(SLASH01_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), SLASH01_RADIUS);
		break;
	case slash02:
		if (islookleft == false) 
		{
			position = Math2D::Add(pos, Vector2D(SLASH02_POS, 0.0f));
		}
		else
		{
			position = Math2D::Sub(pos, Vector2D(SLASH02_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), SLASH02_RADIUS);
		break;
	case slash03:
		if (islookleft == false) 
		{
			position = Math2D::Add(pos, Vector2D(SLASH03_POS, 0.0f));
		}
		else 
		{
			position = Math2D::Sub(pos, Vector2D(SLASH03_POS, 0.0f));
		}
		circleColid = CircleColid(Vector2D(0, 0), SLASH03_RADIUS);
		break;
	}
	objtag = tag;
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
		if (slashtype[slash01].life > 0)
		{
			slashtype[slash01].life -= dt;//斬撃の表示されている時間を減らす
			if (slashtype[slash01].life <= 0)
			{
				DestroyMe();
				break;
			}
			//左を向いているかどうかを確認する
			if (islookleft == true) 
			{
				position.x -= slashtype[slash01].speed * dt;//時間まで左に進む
			}
			else
			{
				position.x += slashtype[slash01].speed * dt;//時間まで右に進む
			}
		}
		break;
	case slash02:
		if (slashtype[slash02].life > 0) 
		{
			slashtype[slash02].life -= dt;
			if (slashtype[slash02].life <= 0)
			{
				DestroyMe();
				break;
			}
			if (islookleft == true) 
			{
				
				position.x -= slashtype[bullet02].speed * dt;
			}
			else 
			{
				
				position.x += slashtype[bullet02].speed * dt;
			}
		}
		break;
	case slash03:
		if (slashtype[slash03].life > 0) 
		{
			slashtype[slash03].life -= dt;
			if (slashtype[slash03].life <= 0)
			{
				DestroyMe();
				break;
			}
			if (islookleft == true)
			{
				position.x -= slashtype[slash03].speed * dt;//時間まで左に進む
			}
			else 
			{
				position.x += slashtype[slash03].speed * dt;//時間まで右に進む
			}
		}
		break;
	}
}

void Slash::Draw()
{
	float posX = position.x - Stage::scrollX;//これでスクロールでも表示されるはず
	float posY = position.y - Stage::GetScrollY();
	DrawCircle(int(posX+16), int(posY+16), (int)slashtype[slashNum_].size, GetColor(255, 255, 255),TRUE);

}
