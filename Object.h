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
        :CenterPosition(0.0f,0.0f),Radius(0.0f)
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
        :Width(0.0f),Height(0.0f)
    {
    }
    BoxColid(float W, float H)
        :Width(W), Height(H)
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
    float GetCollisionRadius() { return circleColid.Radius; }
protected:
    Vector2D position;
    Vector2D radius;
    CircleColid circleColid;
};

namespace ObjectProcess
{
    void HitObject();
}