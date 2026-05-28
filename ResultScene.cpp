#include "ResultScene.h"
#include"DataHolder.h"
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
	int size = GetFontSize();
	SetFontSize(50);
	int CenterX= (WIN_WIDTH / SCREEN_ZOOM)/2;
	int CenterY  = (WIN_HEIGHT / SCREEN_ZOOM)/2;
	DataHolder* dh = FindGameObject<DataHolder>();
	DrawString(CenterX - 3 * GetFontSize() / SCREEN_ZOOM - GetFontSize() / 2,CenterY-50, "Result", GetColor(255, 255, 255));
	DrawFormatString(CenterX - 8 * GetFontSize() / SCREEN_ZOOM - GetFontSize() / 2, CenterY, GetColor(255, 255, 255), "PlayTimer: %d•ª%d•b",(int) gGameTimer.GetTimer()/60, (int)gGameTimer.GetTimer()%60);
	DrawFormatString(CenterX-13*GetFontSize() / SCREEN_ZOOM, CenterY + 50, GetColor(255, 255, 255), "ƒNƒŠƒAƒXƒe[ƒW:ƒXƒe[ƒW %d", dh->GetFinishStageNum());
	DrawFormatString(CenterX-7*GetFontSize() / SCREEN_ZOOM, CenterY + 100, GetColor(255, 255, 255), "Œ‚”j‚µ‚½“G: %d", dh->GetTotalDestroyedEnemyNum());
	//DrawFormatString(CenterX, CenterY + 100, GetColor(255, 255, 255), "Œ‚”j‚µ‚½“G: %d", Player::GetHp());
	//DrawStringF(WIN_WIDTH / 2.0f, 100.0f, "Result",GetColor(255,255,255));
	SetFontSize(size);
}
