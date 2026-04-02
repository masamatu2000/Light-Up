#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
#include"Gimmick.h"
#include"EnemyMove.h"
/// <summary>
/// ìGÇä«óùÇ∑ÇÈ
/// M.Shoji
/// </summary>
namespace {
	const float TRACE_DISTANCE = 32*4;
	const Vector2D ENEMY_SPEED = Vector2D(15, 0);
}
Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2D& pos, ENEMY_NUMBER ENum)
{
	position = pos;
	circleColid = CircleColid(Vector2D(IMAGE_SCALE / 2, IMAGE_SCALE / 2), IMAGE_SCALE / 2);
	EnemyNumber = ENum;
	Velocity = ENEMY_SPEED;
	switch (EnemyNumber) {
	case Enemy01:
		Hp =(unsigned int) EnemyTypeNum::ENEMY_01_HP;
		break;
	case Enemy02:
		Hp = (unsigned int)EnemyTypeNum::ENEMY_02_HP;
		break;
	case TURRET:
		Hp = (unsigned int)EnemyTypeNum::TURRET_HP;
		break;
	case BOMBER:
		Hp = (unsigned int)EnemyTypeNum::BOMBER_HP;
		break;
	}
	timer = 0;
	invincibilityTimeCounter = 0;//ñ≥ìGéûä‘
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (Hp <= 0)
	{
		new  Gimmick(position, GIMMICK_TYPE::Corpse, "Enemy", EnemyNumber);
		DestroyMe();
	}
	/*Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D Distance = Math2D::Sub(ppos, position);
	float dist = Math2D::Length(Distance);*/

	timer += gDeltaTime;
	switch (EnemyNumber) {
	case Enemy01:
		EnemyAttack::Enemy1Attack(position,Velocity,timer);
		break;
	case Enemy02:
		EnemyAttack::Enemy2Attack(position, Velocity,timer);
		break;
	case TURRET:
		EnemyAttack::TurretAttack(position,timer);
		break;
	case BOMBER:
		EnemyAttack::BomberAttack(position, timer);
		break;
	}
	invincibilityTimeCounter--;
}

void Enemy::Draw()
{
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::GetScrollY();

	DrawBoxAA(positionx,positiony,positionx +IMAGE_SCALE,positiony +IMAGE_SCALE, GetColor(0, 0, 255), TRUE);
	DrawFormatString(0, 180, GetColor(255, 255, 255),"X:%f Y:%f HP:%d",position.x,position.y,Hp,TRUE);//ïœêîÇèoóÕÇ∑ÇÈ
}

