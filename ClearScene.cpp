#include "ClearScene.h"
namespace {
	const float CLEAR_TIME = 60 * 5.0f;
}
ClearScene::ClearScene()
{
	timer = 0;
}

ClearScene::~ClearScene()
{}

void ClearScene::Update()
{
	timer++;
	if (timer > CLEAR_TIME || Input::IsKeyDown(INPUT_KEYBOARD) || Input::IsPadDown(Pad::A))
	{
		timer = 0;
		SceneManager::ChangeScene(SCENE_NAME::RESULT_SCENE);
	}
}

void ClearScene::Draw()
{
	int size = GetFontSize();
	SetFontSize(80);
	DrawString(100, 100, "Clear", GetColor(255, 255, 255));
	SetFontSize(size);
}
