#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
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
	IsTrace = false;
	Speed = ENEMY_SPEED.x;
	switch (EnemyNumber) {
	case Enemy01:
		Hp = EnemyTypeNum::ENEMY_01_HP;
		break;
	case Enemy02:
		Hp = EnemyTypeNum::ENEMY_02_HP;
		break;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (Hp <= 0)
	{
		DestroyMe();
	}
	/*Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D Distance = Math2D::Sub(ppos, position);
	float dist = Math2D::Length(Distance);*/
	switch (EnemyNumber) {
	case Enemy01:
		EnemyAttack::Enemy1Attack(position,Velocity);
		break;
	case Enemy02:
		EnemyAttack::Enemy2Attack(position, Velocity);
		break;
	}
}

void Enemy::Draw()
{
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::scrollY;

	DrawBox(positionx,positiony,positionx +IMAGE_SCALE,positiony +IMAGE_SCALE, GetColor(0, 0, 255), TRUE);
	DrawFormatString(0, 180, GetColor(255, 255, 255),"X:%f Y:%f HP:%d",position.x,position.y,Hp,TRUE);//ïœêîÇèoóÕÇ∑ÇÈ
}

