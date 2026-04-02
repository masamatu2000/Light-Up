#pragma once
#include"AttackObject.h"
#include<vector>

enum OBJECT_TAG {
	PLAYER,
	ENEMY,
	BOSS
};
class Bullet :public AttackObject {
public:
	Bullet(const Vector2D &pos,BULLET_NUMBER bulletNum,bool lookleft,OBJECT_TAG tag);
	Bullet(const Vector2D& pos, BULLET_NUMBER bulletNum,Vector2D direction, OBJECT_TAG tag);
	//放物線用コンストラクタ
	Bullet(const Vector2D& pos, Vector2D distance, BULLET_NUMBER bulletNum, OBJECT_TAG tag);
	~Bullet();
	void Update()override;
	void Draw()override;
	OBJECT_TAG Gettag() { return objtag; }
	BULLET_NUMBER GetBulletNum()
	{
		return bulletNum_;
	}
private:
	BULLET_NUMBER bulletNum_;
	struct BulletType {
		float speed;
		float size;
		float life;
	};
	std::vector<BulletType> bullettype;
	bool islookleft;
	OBJECT_TAG objtag;
	//方向ベクトル
	Vector2D dir;
	//差分ベクトル
	Vector2D dis;
	float gravity;
	//速度計算用の関数
	void CalculateVelocity();
};
class Slash :public AttackObject
{
public:
	Slash(const Vector2D& pos, SLASH_NUMBER slashNum,bool lookleft,OBJECT_TAG tag);//コンストラクタに左を向いているかどうかの処理を追加
	~Slash();
	void Update()override;
	void Draw()override;
	OBJECT_TAG Gettag() { return objtag; }
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
	OBJECT_TAG objtag;
};