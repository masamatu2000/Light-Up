#pragma once
#include"AttackObject.h"
#include<vector>

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