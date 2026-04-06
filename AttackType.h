#pragma once
#include"AttackObject.h"
#include<vector>

struct BulletType {
	float vel;
	float rad;
	float life;
	float offsetX;
};

struct SlashType {
	float vel;
	float rad;
	float life;
	float offsetX;
};

class Bullet :public AttackObject {
public:
	Bullet(const Vector2D &pos,BulletNumber bulletNum,bool lookleft,ObjectTag tag);
	//角度指定用コンストラクタ
	Bullet(const Vector2D& pos, BulletNumber bulletNum,Vector2D direction, ObjectTag tag);
	//放物線用コンストラクタ
	Bullet(const Vector2D& pos, Vector2D distance, BulletNumber bulletNum, ObjectTag tag);
	~Bullet();
	void Update()override;
	void Draw()override;
	BulletNumber GetBulletNum()
	{
		return bulletNumber;
	}
private:
	BulletNumber bulletNumber;
	BulletType bulletType;
	
	//差分ベクトル
	Vector2D dis;
	float gravity;
private:
	//速度計算用の関数
	void CalculateVelocity() override;
	//重力計算用の関数
	void CalculateGravity();
	//方向により発射位置の調整
	void SetOffsetPosition() override;
	//ライフの計算、識別
	bool CheckNoLife() override;
	//壁との接触
	bool HitWall();
	//爆弾魔用のUpdate（特殊な動作をするため）
	void UpdateBomber();
};
class Slash :public AttackObject
{
public:
	Slash(const Vector2D& pos, SlashNumber slashNum,bool lookleft,ObjectTag tag);//コンストラクタに左を向いているかどうかの処理を追加
	~Slash();
	void Update()override;
	void Draw()override;
	ObjectTag Gettag() { return objtag; }
private:
	SlashNumber slashNum_;
	SlashType slashType;
private:
	//速度計算用の関数
	void CalculateVelocity() override;
	//方向により発射位置の調整
	void SetOffsetPosition() override;
	//ライフの計算、識別
	bool CheckNoLife() override;
};