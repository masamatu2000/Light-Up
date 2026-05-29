#include "BootScene.h"
#include"DataHolder.h"

/// <summary>
/// 起動時のシーン
/// 共通で必要なGameObjectを生成して、
/// シーンを変更する
/// </summary>
/// <author>H.suginuma</author>


BootScene::BootScene()
{
	DataHolder* dt = new DataHolder();
	dt->fontSize = GetFontSize();
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene(SCENE_NAME::TITLE_SCENE); // 起動が終わったらTitleを表示
}

void BootScene::Draw()
{
}
