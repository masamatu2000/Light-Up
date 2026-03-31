#pragma once
/// <summary>
/// アニメーション時の背景の描画を管理するクラス
/// </summary>
/// <author>H.suginuma</author>

#include"GameObject.h"
#include"DxLib.h"
#include<string>

class Animation : public GameObject
{
public:
	Animation();
	Animation(std::string name);
	~Animation();
	void Update() override;
	void Draw() override;
private:
	float animeTimer;
	int pat;
};