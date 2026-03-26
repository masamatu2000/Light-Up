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
	timer = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	/*Player* pl = FindGameObject<Player>();
	Vector2D ppos = pl->GetPosition();
	Vector2D Distance = Math2D::Sub(ppos, position);
	float dist = Math2D::Length(Distance);*/

	timer++;
	switch (EnemyNumber) {
	case Enemy01:
		EnemyAttack::Enemy1Attack(position,Velocity,timer);
		break;
	case Enemy02:
		EnemyAttack::Enemy2Attack(position, Velocity,timer);
		break;
	}
}

void Enemy::Draw()
{
	float positionx = position.x - Stage::scrollX;
	float positiony = position.y - Stage::scrollY;

	DrawBox(positionx,positiony,positionx +IMAGE_SCALE,positiony +IMAGE_SCALE, GetColor(0, 0, 255), TRUE);
	DrawFormatString(20, 20, GetColor(255, 255, 255),"%f %f",position.x,position.y,TRUE);//ïœêîÇèoóÕÇ∑ÇÈ
}

