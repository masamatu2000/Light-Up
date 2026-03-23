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
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		dh->stageNum -= 1;
		if (dh->stageNum < 1)dh->stageNum = STAGE_MAX;
	}
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		dh->stageNum += 1;
		if (dh->stageNum > STAGE_MAX)dh->stageNum = 1;
	}
	if (Input::IsKeyDown(KEY_INPUT_F))
	{
		state = State::CHARACTER_SELECT;
	}
}

void SelectScene::UpdateChara()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		dh->playerNum -= 1;
		if (dh->playerNum < 1)dh->playerNum= CHARA_MAX;
	}
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		dh->playerNum += 1;
		if (dh->playerNum > CHARA_MAX)dh->playerNum = 1;
	}
	if (Input::IsKeyDown(KEY_INPUT_F))
	{
		SceneManager::ChangeScene(SCENE_NAME::PLAY_SCENE);
	}
}

void SelectScene::DrawStage()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	DrawFormatString(0, 0, 0xffffff, "STAGE : %d", dh->stageNum);
}

void SelectScene::DrawChara()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	DrawFormatString(0, 0, 0xffffff, "CHARA : %d", dh->playerNum);
}
