#pragma once
#include"AttackObject.h"
#include<vector>
enum ATTACK_TYPE
{
	bullet,
	slash
};
enum BULLET_NUMBER
{
	bullet01,
	bullet02
};
enum SLASH_NUMBER
{
	slash01,
	clash02
};
struct Bullet01 {
};
class Bullet :public AttackObject {
public:
	Bullet(const Vector2D &pos,BULLET_NUMBER bulletNum);
	~Bullet();
	void Update()override;
	void Draw()override;
private:
	BULLET_NUMBER bulletNum_;
	struct BulletType {
		float speed;
		float size;
		float life;
	};
	std::vector<BulletType> bullettype;
};