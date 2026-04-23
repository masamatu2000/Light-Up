#include "ResultScene.h"
namespace {
	const float RESULT_TIME = 60 * 5.0f;
}
ResultScene::ResultScene()
{
	timer = 0;
}

ResultScene::~ResultScene()
{}

void ResultScene::Update()
{
	timer++;
	if (timer > RESULT_TIME||Input::IsKeyDown(INPUT_KEYBOARD)||Input::IsPadDown(Pad::A))
	{
		timer = 0;
		SceneManager::ChangeScene(SCENE_NAME::TITLE_SCENE);
	}
}

void ResultScene::Draw()
{
	float size = GetFontSize();
	SetFontSize(80);
	DrawString(100, 100, "Result", GetColor(255, 255, 255));
	SetFontSize(size);
}
