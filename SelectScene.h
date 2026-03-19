#pragma once
#include "SceneBase.h"

/// <summary>
/// ステージとキャラクターの選択をする
/// </summary>
/// <author>H.suginuma</author>
class SelectScene : public SceneBase
{
public:
	SelectScene();
	~SelectScene();
	void Update() override;
	void Draw() override;
private:
	enum State
	{
		//ステージの選択
		STAGE_SELECT,
		//キャラクターの選択
		CHARACTER_SELECT
	};
	State state;
	//ステージ選択用
	void UpdateStage();
	void DrawStage();
	//キャラ選択用
	void UpdateChara();
	void DrawChara();
};