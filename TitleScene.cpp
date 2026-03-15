#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::PLAY_SCENE);
	}
}

void TitleScene::Draw()
{
	DrawString(100,100,"TitleScene", 0xffffff );
	DrawString(100, 120, "Push [N]Key To Play", 0xffffff);
}
