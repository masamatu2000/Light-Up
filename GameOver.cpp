#include "GameOver.h"
namespace {
	const float GAMEOVER_TIME = 60*5.0f;
}
GameOver::GameOver()
{
	timer = 0;
}

GameOver::~GameOver()
{}

void GameOver::Update()
{
		timer++;
		if (timer > GAMEOVER_TIME||Input::IsKeepKeyDown(INPUT_KEYBOARD)||Input::IsPadDown(Pad::A))
		{
			timer = 0;
			SceneManager::ChangeScene(SCENE_NAME::RESULT_SCENE);
		}
}

void GameOver::Draw()
{
	int size = GetFontSize();
	SetFontSize(80);
	DrawString(100, 100, "Game Over",GetColor(255,0,0));
	SetFontSize(size);
}
