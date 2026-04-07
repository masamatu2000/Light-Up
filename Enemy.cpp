#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
#include"Gimmick.h"
#include"EnemyMove.h"
/// <summary>
/// 敵を管理する
/// M.Shoji
/// </summary>
namespace {
	//敵のステータス構造体		　 HP　X速度
	const EnemyStatus KURIBOH   = { 2, 15.0f };
	const EnemyStatus FAIRY     = { 2, 15.0f };
	const EnemyStatus TURRET    = { 3,  0.0f };
	const EnemyStatus GUNDAM    = { 1,  1.0f };
	const EnemyStatus BOMBER    = { 1, 30.0f };
	const EnemyStatus CREEPER   = { 1,  1.0f };
	const EnemyStatus DOKUTARO  = { 1,  1.0f };
	const EnemyStatus DEBUFFER  = { 1,  1.0f };
	const EnemyStatus LANCER    = { 1,  1.0f };
	const EnemyStatus BERSERKER = { 1,  1.0f };
}
Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2D& pos, EnemyNumber ENum)
{
	position = pos;
	circleColid = CircleColid(Vector2D(IMAGE_SCALE / 2, IMAGE_SCALE / 2), IMAGE_SCALE / 2);
	enemyNumber = ENum;
	switch (enemyNumber) {
	case EnemyNumber::KURIBOH:
		enemyStatus = KURIBOH;
		break;
	case EnemyNumber::FAIRY:
		enemyStatus = FAIRY;
		break;
	case EnemyNumber::TURRET:
		enemyStatus = TURRET;
		break;
	case EnemyNumber::BOMBER:
		enemyStatus = BOMBER;
		break;
	}
	timer = 0;
	invincibilityTimeCounter = 0;//無敵時間
	SetStatus();
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

	switch (enemyNumber) {
	case EnemyNumber::KURIBOH:
		EnemyAttack::Enemy1Attack(position,Velocity,timer);
		break;
	case EnemyNumber::FAIRY:
		EnemyAttack::Enemy2Attack(position, Velocity,timer);
		break;
	case EnemyNumber::TURRET:
		EnemyAttack::TurretAttack(position,timer);
		break;
	case EnemyNumber::BOMBER:
		EnemyAttack::BomberAttack(position,Velocity, timer);
		break;
	}
}

void Enemy::Draw()
{
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::GetScrollY();

	DrawBoxAA(positionx,positiony,positionx +IMAGE_SCALE,positiony +IMAGE_SCALE, GetColor(0, 0, 255), TRUE);
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
}

