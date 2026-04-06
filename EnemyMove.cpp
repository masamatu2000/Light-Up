#include "EnemyMove.h"
#include"Math2D.h"
#include"Player.h"
#include"Stage.h"
#include"Enemy.h"
#include"AttackType.h"
namespace {
	const float GRAVITY = 9.8f * 60 * 2;
	const float TRACE_DISTANCE =IMAGE_SCALE * 10;
	const float ENEMY_BULLET_COOLTIME = 2.0f;
	const float ENEMY1_ATTACK_DISTANCE = IMAGE_SCALE * 2;
	const float ENEMY2_ATTACK_DISTANCE = IMAGE_SCALE * 10;
}
//タレット用の定数
namespace Turret
{
	//タレットの継続時間
	const float SHOT_TIME = 1.0f;
	const float COOLTIME = 3.0f;
	const float ATTACK_DISTANCE = IMAGE_SCALE * 15;
}
//ボマー用の定数
namespace Bomber
{
	//最高到達地点
	const float MAX_HEIGHT = IMAGE_SCALE * 2;
	//最高到達点までの時間
	const float MAX_TIME = 1.0f;
	const float COOLTIME = 3.0f;
	const float ATTACK_DISTANCE = IMAGE_SCALE * 5;
}

void EnemyAttack::Enemy1Attack(const Vector2D& pos, const Vector2D& vel,const int &timer)
{
	Vector2D epos = pos;
	Vector2D evel = vel;
	auto e=FindGameObjects<Enemy>();
	Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D distance = Math2D::Sub(ppos, epos);
	float dx = distance.x;
	distance.x = abs(distance.x);
	distance.y = abs(distance.y);
	distance.x = abs(distance.x);
	distance.y = abs(distance.y);
	bool IsAttack = false;
	float dt = GetDeltaTime();
	Stage* stage = FindGameObject<Stage>();
	if (distance.x < TRACE_DISTANCE) {
		float speed = abs(vel.x);
		float dt = GetDeltaTime();
		// ★ 向きだけ決める
		float dir = (dx > 0) ? 1.0f : -1.0f;
		epos.x += dir * speed*dt;
	}
	else {
		epos.x += vel.x * dt;
		if (vel.x > 0) {
			int d1 = stage->HitWallRight(int(pos.x + IMAGE_SCALE - 1),int( pos.y + IMAGE_SCALE - 1));
			int d2 = stage->HitWallRight(int(pos.x + IMAGE_SCALE - 1),int( pos.y));

			int d = max(d1, d2);
			if (d > 0)
			{
				evel.x *= -1;
			}

			epos.x -= max(d1, d2);
		}
		else if (vel.x < 0)
		{
			int d1 = stage->HitWallLeft(int(pos.x + 0), int(pos.y + IMAGE_SCALE - 1));
			int d2 = stage->HitWallLeft(int(pos.x + 0), int(pos.y));

			int d = max(d1, d2);
			if (d > 0)
			{
				evel.x *= -1;
			}

			epos.x += max(d1, d2);
		}
	}
	evel.y += GRAVITY * dt;
	epos.y += evel.y * dt;
	int d1 = stage->HitFloor(int(pos.x + 0), int(pos.y + IMAGE_SCALE));
	int d2 = stage->HitFloor(int(pos.x + IMAGE_SCALE - 1), int(pos.y + IMAGE_SCALE));

	int d = max(d1, d2);

	if (d > 0) {
		epos.y -= (d - 1);
		evel.y = 0;
	}

	if (timer > ENEMY_BULLET_COOLTIME&&distance.x <= ENEMY1_ATTACK_DISTANCE && distance.y <= ENEMY1_ATTACK_DISTANCE) {
		IsAttack = true;
		new Slash(pos, SlashNumber::BASE , (dx < 0), ObjectTag::ENEMY);
		
	}
	for (auto enemy : e) {
		if (enemy->GetEnum() == Enemy01) {
			enemy->SetPosition(epos);
			enemy->SetVel(evel);
			if (IsAttack) {
				enemy->SetTimer(0);
			}
		}
	}
	
}

void EnemyAttack::Enemy2Attack(const Vector2D& pos,const Vector2D & vel,const int &timer)
{
	Vector2D epos = pos;
	Vector2D evel = vel;
	Player* pl = FindGameObject<Player>();
	auto e = FindGameObjects<Enemy>();
	static float t = 0.0f;
	epos.y = epos.y +1.0f * sinf(15.0f * t);//上下に動くやつ
	t = t + gDeltaTime;
	float dt = GetDeltaTime();
	Stage* stage = FindGameObject<Stage>();
	epos.x += evel.x * dt;
	bool IsAttack = false;
	Vector2D ppos = pl->GetPosition();
	Vector2D distance = Math2D::Sub(ppos, epos);
	distance.x = abs(distance.x);
	distance.y = abs(distance.y);
	float dx = abs(ppos.x - epos.x);
	if (evel.x > 0) {
		int d1 = stage->HitWallRight(int(epos.x + IMAGE_SCALE - 1),int( epos.y + IMAGE_SCALE - 1));
		int d2 = stage->HitWallRight(int(epos.x + IMAGE_SCALE - 1), int(epos.y));

		int d = max(d1, d2);
		if (d > 0)
		{
			evel.x *= -1;
		}

		epos.x -= max(d1, d2);
	}
	else if (evel.x < 0)
	{
		int d1 = stage->HitWallLeft(int(epos.x + 0), int(epos.y + IMAGE_SCALE - 1));
		int d2 = stage->HitWallLeft(int(epos.x + 0), int(epos.y));

		int d = max(d1, d2);
		if (d > 0)
		{
			evel.x *= -1;
		}

		epos.x += max(d1, d2);
	}
	int d1 = stage->HitFloor(int(epos.x + 0), int(epos.y + IMAGE_SCALE));
	int d2 = stage->HitFloor(int(epos.x + IMAGE_SCALE - 1), int(epos.y + IMAGE_SCALE));

	int d = max(d1, d2);

	if (d > 0) {
		epos.y -= (d - 1);
		evel.y = 0;
	}
	if (timer > ENEMY_BULLET_COOLTIME&&distance.x<= ENEMY2_ATTACK_DISTANCE&&distance.y<= ENEMY2_ATTACK_DISTANCE) {
		IsAttack = true;
		Player* pl = FindGameObject<Player>();
		Vector2D distance = Math2D::Sub(pl->GetPosition(), epos);
		Vector2D dir = Math2D::Normalize(distance);
		float Rad = 30 * (DX_PI_F / 180.0f);
		Vector2D Rotation = { (dir.x * cosf(Rad) - dir.y * sinf(Rad)),(dir.x * sinf(Rad) + dir.y * cosf(Rad)) };//(dir.x * cosf(-Rad) - dir.y * sinf(-Rad)),(dir.x * sinf(-Rad) + dir.y * cosf(-Rad))
		Vector2D Rotation2 = { (dir.x * cosf(-Rad) - dir.y * sinf(-Rad)),(dir.x * sinf(-Rad) + dir.y * cosf(-Rad)) };
		new Bullet(pos, BulletNumber::FAIRY,dir,ObjectTag::ENEMY);
		new Bullet(pos, BulletNumber::FAIRY,Rotation, ObjectTag::ENEMY);
		new Bullet(pos, BulletNumber::FAIRY,Rotation2 , ObjectTag::ENEMY);
	}
	for (auto enemy : e) {
		if (enemy->GetEnum() == Enemy02) {
			enemy->SetPosition(epos);
			enemy->SetVel(evel);
			if (IsAttack) {
				enemy->SetTimer(0);
			}
		}
	}
	
}

void EnemyAttack::TurretAttack(const Vector2D& pos, const int& timer)
{
	Vector2D ePos = pos;
	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	//プレイヤーとの距離
	float distance = Math2D::Length(Math2D::Sub(pPos, pos));
	//レーザーの方向ベクトル 攻撃可能になった時にだけ設定する
	static Vector2D dir = { 0,0 };
	//攻撃が可能かどうか
	static bool isAttack = false;
	//攻撃時間（1秒間）を管理する用のタイマー
	static float shotTimer = 0.0f;

	//距離が一定以下かつ、クールタイムが終わっているなら攻撃可能に
	if (distance < Turret::ATTACK_DISTANCE && timer > Turret::COOLTIME)
	{
		isAttack = true;
		dir = Math2D::Normalize(Math2D::Sub(pPos, ePos));
		auto e = FindGameObjects<Enemy>();
		for (auto enemy : e) {
			if (enemy->GetEnum() == ENEMY_NUMBER::TURRET) {
				enemy->SetTimer(0);
			}
		}
	}

	if (isAttack)
	{
		if (shotTimer < Turret::SHOT_TIME)
		{
			shotTimer += gDeltaTime;
			new Bullet(ePos, BulletNumber::TURRET, dir, ObjectTag::ENEMY);
			if (shotTimer >= Turret::SHOT_TIME)
			{
				shotTimer = 0.0f;
				dir = { 0,0 };
				isAttack = false;
			}
		}
	}
}

void EnemyAttack::BomberAttack(const Vector2D& pos, const Vector2D& vel, const int& timer)
{
	Vector2D ePos = pos;
	Vector2D eVel = vel;
	Player* pl = FindGameObject<Player>();
	Vector2D pPos = pl->GetPosition();
	//プレイヤーとの距離（ベクトル）
	Vector2D dis = Math2D::Sub(pPos, ePos);
	//プレイヤーとの距離（距離）
	float distance = Math2D::Length(dis);
	//攻撃が可能かどうか
	static bool isAttack = false;
	//ステージのポインタ
	Stage* s = FindGameObject<Stage>();
	//敵すべてのポインタ（ここから検索）
	auto e = FindGameObjects<Enemy>();
	//ボマー保存用のポインタ
	Enemy* bomber = nullptr;
	for (auto enemy : e)
	{
		if (enemy->GetEnum() == ENEMY_NUMBER::BOMBER)
		{
			bomber = enemy;
			break;
		}
	}
	//フレーム間時間
	float dt = GetDeltaTime();

	//距離が一定以下かつ、クールタイムが終わっているなら攻撃可能に
	//この間は移動しない
	if (distance < Bomber::ATTACK_DISTANCE)
	{
		if (timer > Bomber::COOLTIME)
		{
			isAttack = true;
			bomber->SetTimer(0);
		}
	}
	else {
		//X座標の更新
		ePos.x += eVel.x * dt;
		if (eVel.x > 0) {
			int d1 = s->HitWallRight(int(ePos.x + IMAGE_SCALE - 1), int(ePos.y + IMAGE_SCALE - 1));
			int d2 = s->HitWallRight(int(ePos.x + IMAGE_SCALE - 1), int(ePos.y));

			int d = max(d1, d2);
			if (d > 0)
			{
				eVel.x *= -1;
			}

			ePos.x -= max(d1, d2);
		}
		else if (eVel.x < 0)
		{
			int d1 = s->HitWallLeft(int(ePos.x + 0), int(ePos.y + IMAGE_SCALE - 1));
			int d2 = s->HitWallLeft(int(ePos.x + 0), int(ePos.y));

			int d = max(d1, d2);
			if (d > 0)
			{
				eVel.x *= -1;
			}

			ePos.x += max(d1, d2);
		}
	}
	//重力処理
	eVel.y += GRAVITY * dt;
	//Y座標の更新
	ePos.y += eVel.y * dt;
	int d1 = s->HitFloor(int(ePos.x + 0), int(ePos.y + IMAGE_SCALE));
	int d2 = s->HitFloor(int(ePos.x + IMAGE_SCALE - 1), int(ePos.y + IMAGE_SCALE));

	int d = max(d1, d2);

	if (d > 0) {
		ePos.y -= (d - 1);
		eVel.y = 0;
	}

	//座標と速度をセット
	bomber->SetPosition(ePos);
	bomber->SetVel(eVel);
	
	if (isAttack)
	{
		//放物線を描くバレットを生成
		new Bullet(ePos, dis, BulletNumber::BOMBER, ObjectTag::ENEMY);
		isAttack = false;
	}
}
