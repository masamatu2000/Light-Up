#include "EnemyMove.h"
#include"Math2D.h"
#include"Player.h"
#include"Stage.h"
#include"Enemy.h"
#include"AttackType.h"
/// <summary>
/// とりあえず移動の関数、SetTimerの関数も作った。Attack関数も作ろうかなと思ったけど、せっかくEnemyAttackがあるのにまた別のところで呼び出したら
/// EnemyAttackの意味がなくなってしまうと思ったので、EnemyAttackの中で呼び出すようにした。まあ、頼むわ＾＾
/// </summary
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
	Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D distance = Math2D::Sub(ppos, epos);
	float dt = GetDeltaTime();
	Stage* stage = FindGameObject<Stage>();
	Move(epos, evel, Enemy01);
	if (timer > ENEMY_BULLET_COOLTIME&&distance.x <= ENEMY1_ATTACK_DISTANCE && distance.y <= ENEMY1_ATTACK_DISTANCE) {//攻撃
		new Slash(pos, SLASH_NUMBER::slash01 , (distance.x < 0), OBJECT_TAG::ENEMY);
		AttackReset(Enemy01,nullptr);
	}	
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
		new Slash(pos, SLASH_NUMBER::slash01 , (dx < 0), OBJECT_TAG::ENEMY);
		
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
	float dt = GetDeltaTime();
	Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D distance = Math2D::Sub(ppos, epos);
	//↓移動と壁のヒットチェック
	Move(epos, evel,Enemy02);
	if (timer > ENEMY_BULLET_COOLTIME && distance.x <= ENEMY2_ATTACK_DISTANCE && distance.y <= ENEMY2_ATTACK_DISTANCE) {//攻撃
		Vector2D dir = Math2D::Normalize(distance);
		float Rad = 30 * (DX_PI_F / 180.0f);
		Vector2D Rotation = { (dir.x * cosf(Rad) - dir.y * sinf(Rad)),(dir.x * sinf(Rad) + dir.y * cosf(Rad)) };//(dir.x * cosf(-Rad) - dir.y * sinf(-Rad)),(dir.x * sinf(-Rad) + dir.y * cosf(-Rad))
		Vector2D Rotation2 = { (dir.x * cosf(-Rad) - dir.y * sinf(-Rad)),(dir.x * sinf(-Rad) + dir.y * cosf(-Rad)) };
		new Bullet(pos, BULLET_NUMBER::bullet04,dir,OBJECT_TAG::ENEMY);
		new Bullet(pos, BULLET_NUMBER::bullet04,Rotation, OBJECT_TAG::ENEMY);
		new Bullet(pos, BULLET_NUMBER::bullet04,Rotation2 , OBJECT_TAG::ENEMY);
		AttackReset(Enemy02, nullptr);
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
		AttackReset(TURRET, nullptr);
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
			AttackReset(BOMBER, bomber);
		}
	}
	else {
		Move(ePos, eVel, BOMBER);
	}
	if (isAttack)
	{
		//放物線を描くバレットを生成
		new Bullet(ePos, dis, BULLET_NUMBER::BOMBER_BULLET, OBJECT_TAG::ENEMY);
		
		isAttack = false;
	}
}

void Move(Vector2D& pos, Vector2D& vel,ENEMY_NUMBER Enum)
{

	Stage* stage = FindGameObject<Stage>();
	float dt = GetDeltaTime();
	auto e = FindGameObjects<Enemy>();
	//↓Enemy01の変数（swicth文の中で宣言できないので）
	Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D distance = Math2D::Sub(ppos, pos);
	float dx = distance.x;
	distance.x = abs(distance.x);
	distance.y = abs(distance.y);
	float dir = (dx > 0) ? 1.0f : -1.0f;
	bool IsTrace = false;
	//↓Enemy02の変数
	static float t = 0.0f;
	switch (Enum)
	{
	case Enemy01:
		if (distance.x< TRACE_DISTANCE) {//プレイヤーを追跡する
			pos.x += dir * abs(vel.x) * dt;
			IsTrace = true;
			break;
		}
		pos.x += vel.x * dt;
		break;
	case Enemy02:
		pos.y = pos.y + 1.0f * sinf(15.0f * t);//上下に動くやつ
		t = t + gDeltaTime;
		pos.x += vel.x * dt;
		break;
	case TURRET:
		break;
	case GUNDAM:
		break;
	case BOMBER:
		pos.x += vel.x * dt;
		break;
	case CREEPER:
		break;
	case DOKUTARO:
		break;
	case DEBUFFER:
		break;
	case LANCER:
		break;
	case BERSERKER:
		break;
	}
	if (!IsTrace) {
		if (vel.x > 0) {
			int d1 = stage->HitWallRight(int(pos.x + IMAGE_SCALE - 1), int(pos.y + IMAGE_SCALE - 1));
			int d2 = stage->HitWallRight(int(pos.x + IMAGE_SCALE - 1), int(pos.y));

			int d = max(d1, d2);
			if (d > 0)
			{
				vel.x *= -1;
			}
			pos.x -= max(d1, d2);
		}
		else if (vel.x < 0)
		{
			int d1 = stage->HitWallLeft(int(pos.x + 0), int(pos.y + IMAGE_SCALE - 1));
			int d2 = stage->HitWallLeft(int(pos.x + 0), int(pos.y));
			int d = max(d1, d2);
			if (d > 0)
			{
				vel.x *= -1;
			}
			pos.x += max(d1, d2);
		}
	}
	if (Enum != Enemy02) {
		vel.y += GRAVITY * dt;
		pos.y += vel.y * dt;
		int d1 = stage->HitFloor(int(pos.x + 0), int(pos.y + IMAGE_SCALE));
		int d2 = stage->HitFloor(int(pos.x + IMAGE_SCALE - 1), int(pos.y + IMAGE_SCALE));

		int d = max(d1, d2);

		if (d > 0) {
			pos.y -= (d - 1);
			vel.y = 0;
		}
	}
	for (auto enemy : e) {
		if (enemy->GetEnum() == Enum) {
			enemy->SetPosition(pos);
			enemy->SetVel(vel);
		}
	}
}

void AttackReset(ENEMY_NUMBER Enum,Enemy* enemy=nullptr)
{
	auto e = FindGameObjects<Enemy>();
	switch (Enum)
	{
	case Enemy01:
	case Enemy02:
	case TURRET:
		for (auto enemy : e) {
			if (enemy->GetEnum() == Enum) {
				enemy->SetTimer(0);
			}
		}
		return;
	case GUNDAM:
		break;
	case BOMBER:
		enemy->SetTimer(0);
		break;
	case CREEPER:
		break;
	case DOKUTARO:
		break;
	case DEBUFFER:
		break;
	case LANCER:
		break;
	case BERSERKER:
		break;
	}
}
