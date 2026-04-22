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
struct LineColid
{
    Vector2D start;
    Vector2D end;
    float radius;
    LineColid()
        :start{ 0,0 }, end{ 0,0 }, radius(0.0f)
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
    float GetCollisionRadius() { return circleColid.Radius; }
    float GetCollisionLineRadius() { return lineColid.radius; }
    Vector2D GetLineStart() { return lineColid.start; }
    Vector2D GetLineEnd() { return lineColid.end; }
    Vector2D GetCollisionCenterPosition() { return circleColid.CenterPosition; }
    float GetDist(Vector2D start, Vector2D end, Vector2D target);
protected:
    Vector2D position;
    Vector2D radius;
    CircleColid circleColid;
    LineColid lineColid;
};

namespace ObjectProcess
{
    void HitObject();
}