#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void Update();
	virtual void Draw();
	virtual void Initialize();
	virtual void Release();
};