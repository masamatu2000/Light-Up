#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
#include"Gimmick.h"
/// <summary>
/// 敵を管理する
/// M.Shoji
/// </summary>
namespace {
	//敵のステータス構造体		　 HP　X速度　　CT　　　　　　　Rad　　　　　攻撃距離　　　 トレース距離
	const EnemyStatus KURIBOH   = { 2, 15.0f, 2.0f, CHARACTER_IMAGE_SCALE / 2, IMAGE_SCALE * 4,   IMAGE_SCALE * 10 };
	const EnemyStatus FAIRY     = { 2, 15.0f, 2.0f, CHARACTER_IMAGE_SCALE / 2, IMAGE_SCALE * 10,                 0 };
	const EnemyStatus TURRET    = { 3,  0.0f, 3.0f, CHARACTER_IMAGE_SCALE / 2, IMAGE_SCALE * 15,                 0 };
	const EnemyStatus GUNDAM    = { 1,  1.0f, 1.0f, CHARACTER_IMAGE_SCALE / 2,                1,                 0 };
	const EnemyStatus BOMBER    = { 1, 30.0f, 3.0f, CHARACTER_IMAGE_SCALE / 2, IMAGE_SCALE *  5,                 0 };
	const EnemyStatus CREEPER   = { 1,  1.0f, 1.0f, CHARACTER_IMAGE_SCALE / 2,                1,                 0 };
	const EnemyStatus DOKUTARO  = { 1,  1.0f, 1.0f, CHARACTER_IMAGE_SCALE / 2,                1,                 0 };
	const EnemyStatus DEBUFFER  = { 1,  1.0f, 1.0f, CHARACTER_IMAGE_SCALE / 2,                1,                 0 };
	const EnemyStatus LANCER    = { 1,  1.0f, 1.0f, CHARACTER_IMAGE_SCALE / 2,                1,                 0 };
	const EnemyStatus BERSERKER = { 1,  1.0f, 1.0f, CHARACTER_IMAGE_SCALE / 2,                1,                 0 };
}
Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (Hp <= 0)
	{
		new  Gimmick(position, GIMMICK_TYPE::Corpse, "Enemy", (int)enemyNumber);
		DestroyMe();
	}

	timer += gDeltaTime;
	invincibilityTimeCounter--;
}

void Enemy::Draw()
{
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::GetScrollY();

	DrawBoxAA(positionx,positiony,positionx + CHARACTER_IMAGE_SCALE,positiony + CHARACTER_IMAGE_SCALE, GetColor(0, 0, 255), TRUE);
	DrawFormatString(0, 180, GetColor(255, 255, 255),"X:%f Y:%f HP:%d",position.x,position.y,Hp,TRUE);//変数を出力する
}

void Enemy::Attack()
{
}

void Enemy::Move()
{
}

void Enemy::SetStatus()
{
	Hp = enemyStatus.hp;
	Velocity.x = enemyStatus.velocityX;
	circleColid = CircleColid(Vector2D(CHARACTER_IMAGE_SCALE / 2, CHARACTER_IMAGE_SCALE / 2), enemyStatus.rad);
}

EnemyStatus Enemy::GetEnemyStatus(EnemyNumber eNum)
{
	//HP　X速度　CT　攻撃距離　トレース距離（トレースしない敵は0）
	switch (eNum)
	{
	case EnemyNumber::KURIBOH:
		return KURIBOH;
		break;
	case EnemyNumber::FAIRY:
		return FAIRY;
		break;
	case EnemyNumber::TURRET:
		return TURRET;
		break;
	case EnemyNumber::GUNDAM:
		return GUNDAM;
		break;
	case EnemyNumber::BOMBER:
		return BOMBER;
		break;
	case EnemyNumber::CREEPER:
		return CREEPER;
		break;
	case EnemyNumber::DOKUTARO:
		return DOKUTARO;
		break;
	case EnemyNumber::DEBUFFER:
		return DEBUFFER;
		break;
	case EnemyNumber::LANCER:
		return LANCER;
		break;
	case EnemyNumber::BERSERKER:
		return BERSERKER;
		break;
	default:
		return{};
		break;
	}
}

float Enemy::CheckHitWall(std::string wall)
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

