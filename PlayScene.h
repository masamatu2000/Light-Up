#pragma once
#include "SceneBase.h"

/// <summary>
/// プレイ中の画面の遷移をする
/// </summary>
/// <author>H.suginuma</author>

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	float time;
	enum State
	{
		//初期のスタートアニメーション用
		START,
		//プレイ中
		PLAY,
		//ボス撃破後
		CLEAR,
		//ゲームオーバー
		OVER,
		//リザルトシーン
		RESULT
	};
	State state;
	void UpdateStart();
	void UpdatePlay();
	void UpdateClear();
	void UpdateOver();
	void UpdateResult();
};