#pragma once
#include "GameObject.h"

/// <summary>
/// オブジェクトの管理
/// </summary>
/// <author>H.suginunma</author>


struct CircleColid
{
    Vector2D CenterPosition;
    float Radius;

    CircleColid()
        :CenterPosition(0.0f,0.0f),Radius(-1.0f)
    {
    }
    CircleColid(Vector2D Cpos,float Rad)
        :CenterPosition(Cpos),Radius(Rad)
    {
    }
    float GetCollisionRadius() { return Radius; }
};
struct BoxColid
{
    float Width;
    float Height;
    BoxColid()
        :Width(-1.0f),Height(-1.0f)
    {
    }
    BoxColid(float W, float H)
        :Width(W), Height(H)
    {
    }
};
struct LineColid
{
    Vector2D start;
    Vector2D end;
    float radius;
    LineColid()
        :start{ 0,0 }, end{ 0,0 }, radius(-1.0f)
    {
    }
    LineColid(Vector2D s, Vector2D e, float rad)
        :start(s), end(e), radius(rad)
    {
    }
};
class Object :public GameObject
{
public:
	Object();
	~Object();
    Vector2D GetPosition() { return position; }
    void SetPosition(Vector2D pos) { position = pos; }
protected:
    Vector2D position;
    Vector2D radius;
    CircleColid circleColid;
    LineColid lineColid;
//当たり判定で使用する用の関数
public:
    //当たり判定の範囲取得用
    float GetCollisionRadius() { return circleColid.Radius; }
    float GetCollisionLineRadius() { return lineColid.radius; }
    //レーザーの当たり判定取得用
    Vector2D GetLineStart() { return lineColid.start; }
    Vector2D GetLineEnd() { return lineColid.end; }
    Vector2D GetCollisionCenterPosition() { return circleColid.CenterPosition; }
    float GetDist(Vector2D start, Vector2D end, Vector2D target);
};

namespace ObjectProcess
{
    void HitObject();
    //プレイヤーにダメージを与える
    void PlayerTakeDamage();
    //プレイヤーの攻撃の判定
    //void AttackForPlayer(const AttackObject* attack);
    //敵、ボスの攻撃の判定
    //void AttackForEnemy(const AttackObject* attack);
}