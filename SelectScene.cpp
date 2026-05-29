#include "SelectScene.h"
#include"DataHolder.h"
/// <summary>
/// ステージとキャラクターの選択をする
/// </summary>
/// <author>H.suginuma</author>

namespace
{
	const int STAGE_MAX = 4;
	const int CHARA_MAX = 3;
}

SelectScene::SelectScene()
{
	state = State::STAGE_SELECT;
}

SelectScene::~SelectScene()
{
}

void SelectScene::Update()
{
	switch (state)
	{
	case STAGE_SELECT :
	{
		UpdateStage();
		break;
	}
	case CHARACTER_SELECT :
	{
		UpdateChara();
		break;
	}
	}
}

void SelectScene::Draw()
{
	switch (state)
	{
	case STAGE_SELECT:
	{
		DrawStage();
		break;
	}
	case CHARACTER_SELECT:
	{
		DrawChara();
		break;
	}
	}
	DrawString(0, 30, "A,Dで選択", 0xffffff);
	DrawString(0, 60, "Fで決定", 0xffffff);
}

void SelectScene::UpdateStage()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	dh;
	if (Input::IsKeyDown(KEY_INPUT_A) || Input::IsPadDown(Pad::LEFT))
	{
		dh->stageNum -= 1;
		if (dh->stageNum < 1)dh->stageNum = STAGE_MAX;
	}
	if (Input::IsKeyDown(KEY_INPUT_D) || Input::IsPadDown(Pad::RIGHT))
	{
		dh->stageNum += 1;
		if (dh->stageNum > STAGE_MAX)dh->stageNum = 1;
	}
	if (Input::IsKeyDown(KEY_INPUT_F) || Input::IsPadDown(Pad::A))
	{
		state = State::CHARACTER_SELECT;
	}
	
	if (Input::IsKeyDown(KEY_INPUT_RETURN) || Input::IsPadDown(Pad::OPTION))
	{
		dh->isTutorialSkip = (dh->isTutorialSkip) ? false : true;
	}
}

void SelectScene::UpdateChara()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	if (Input::IsKeyDown(KEY_INPUT_A) || Input::IsPadDown(Pad::LEFT))
	{
		dh->playerNum -= 1;
		if (dh->playerNum < 1)dh->playerNum= CHARA_MAX;
	}
	if (Input::IsKeyDown(KEY_INPUT_D) || Input::IsPadDown(Pad::RIGHT))
	{
		dh->playerNum += 1;
		if (dh->playerNum > CHARA_MAX)dh->playerNum = 1;
	}
	if (Input::IsKeyDown(KEY_INPUT_F) || Input::IsPadDown(Pad::A))
	{
		SceneManager::ChangeScene(SCENE_NAME::PLAY_SCENE);
	}
}

void SelectScene::DrawStage()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	DrawFormatString(0, 0, 0xffffff, "STAGE : %d", dh->stageNum);
	
	Vector2D p, p2;
	int size = 10;
	p = { 80,0 };
	p2 = { p.x + size,p.y + size };
	DrawBox(p.x,p.y,p2.x,p2.y, 0xffffff, FALSE);
	if (dh->isTutorialSkip)DrawLine(p.x, p.y, p2.x, p2.y, 0xffffff);
	DrawString(p2.x + 5, p.y, "チュートリアルスキップ：エンターで切り替え", 0xffffff);
}

void SelectScene::DrawChara()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	DrawFormatString(0, 0, 0xffffff, "CHARA : %d", dh->playerNum);
}
