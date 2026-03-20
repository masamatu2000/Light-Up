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
class Slash :public AttackObject
{
public:
	Slash(const Vector2D& pos, SLASH_NUMBER slashNum);
	~Slash();
	void Update()override;
	void Draw()override;
private:
	SLASH_NUMBER slashNum_;
	struct SlashType {
		float speed;
		float size;
		float life;
	};
	std::vector<SlashType> slashtype;

};