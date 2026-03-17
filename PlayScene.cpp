#include "PlayScene.h"
#include"Stage.h"
#include "EffectManager.h"

PlayScene::PlayScene()
{
	new Stage();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::TITLE_SCENE);
	}
	
}

void PlayScene::Draw()
{
	DrawString(100, 100, "PlayScene", 0xffffff);
	DrawString(100, 120, "Push [N]Key To Title", 0xffffff);
}
