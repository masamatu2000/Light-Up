#pragma once
/// <summary>
/// アニメーション時の背景の描画を管理するクラス
/// </summary>
/// <author>H.suginuma</author>

#include"GameObject.h"
#include<string>

enum Name
{
	START,
	CLEAR
};

class Animation : public GameObject
{
public:
	Animation();
	Animation(Name name);
	~Animation();
	void Update() override;
	void Draw() override;
private:
	float animeTimer;
	int patX,patY;
	Name animeName;
	//アニメーション時のプレイヤーの位置
	Vector2D position;
	//イージング用の初期値保存用変数
	Vector2D startPos;
	//プレイヤーの画像を保存
	int playerImage;
	//ボスの死体画像を保存
	int corpseImage;

	void InitializeStart();
	void InitializeClear();
	void UpdateStart();
	void UpdateClear();
	void DrawStart();
	void DrawClear();
	//スクロール
	void Scroll();
};