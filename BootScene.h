#pragma once

#include"SceneBase.h"

/// <summary>
/// 起動時のシーン
/// 共通で必要なGameObjectを生成して、
/// シーンを変更する
/// </summary>
/// <author>H.suginuma</author>

class BootScene : public SceneBase
{
public:
	BootScene();
	~BootScene();
	void Update() override;
	void Draw() override;
};