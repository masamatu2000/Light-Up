#pragma once
#include "GameObject.h"

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
class Object : GameObject
{
public:
	Object();
	~Object();

    static int scrollX;
    static int scrollY;
protected:
    Vector2D position;
};