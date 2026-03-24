#pragma once
#include"AttackObject.h"
#include<vector>

class Bullet :public AttackObject {
public:
	Bullet(const Vector2D &pos,BULLET_NUMBER bulletNum,bool lookleft);
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
	struct BulletType2 {
		float speed;
		float size;
		float life;
	};
	std::vector<BulletType2> bullettype2;
	struct BulletType3 {
		float speed;
		float size;
		float life;
	};
	std::vector<BulletType3> bullettype3;
	bool islookleft;
};
class Slash :public AttackObject
{
public:
	Slash(const Vector2D& pos, SLASH_NUMBER slashNum,bool lookleft);//コンストラクタに左を向いているかどうかの処理を追加
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
	struct SlashType2 {
		float speed;
		float size;
		float life;
	};
	std::vector<SlashType2> slashtype2;
	
	struct SlashType3 {
		float speed;
		float size;
		float life;
	};
	std::vector<SlashType3> slashtype3;
	bool islookleft;
};