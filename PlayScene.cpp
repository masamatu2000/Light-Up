#include "PlayScene.h"
#include"Stage.h"
#include"Player.h"
#include "StageGraphic.h"
#include"ImageManager.h"
#include "UserInterface.h"
#include "Animation.h"
#include "SoundManager.h"
#include"DataHolder.h"
/// <summary>
/// プレイ中の画面の遷移をする
/// </summary>
/// <author>H.suginuma</author>

PlayScene::PlayScene()
{
	new Image();
	new Stage();
	state = State::START;
	time = 0;
	new StageGraphic();
	new UserInterface();
	new Sound();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	gGameTimer.Update();
	switch (state)
	{
	case START:
	{
		UpdateStart();
		break;
	}
	case PLAY:
	{
		UpdatePlay();
		break;
	}
	case CLEAR:
	{
		UpdateClear();
		break;
	}
	case OVER:
	{
		UpdateOver();
		break;
	}
	case RESULT:
		UpdateResult();
		break;
	}
	if ((Input::IsKeyDown(KEY_INPUT_N) && ObjectManager::PoseNow()) || (Input::IsPadDown(Pad::OPTION) && ObjectManager::PoseNow()))
	{
		//SceneManager::ChangeScene(SCENE_NAME::TITLE_SCENE);
		DataHolder* dh = FindGameObject<DataHolder>();
		Stage* s = FindGameObject<Stage>();
		dh->SetFinishStageNum((s->GetStageNum()));
		SceneManager::ChangeScene(SCENE_NAME::RESULT_SCENE);
	}
	
}

void PlayScene::Draw()
{
	if (isDebug)
	{
		DrawString(100, 0, "PlayScene", 0xffffff);
		DrawString(100, 20, "Push [U]Key To Pose", 0xffffff);
	}
	if (ObjectManager::PoseNow())
	{
		DrawString(200, 200, "Nで終了", 0xffffff);
		DrawString(200, 220, "Uで解除", 0xffffff);
	}
}

void PlayScene::UpdateStart()
{
	//if (time < 1.0f) {
	//	float dt = GetDeltaTime();
	//	time += dt;
	//	if (time >= 1.0f) {
	//		//1秒たったらPLAYに移行
	//		state = State::PLAY;
	//		time = 0;
	//	}
	//}
	state = State::PLAY;
}

void PlayScene::UpdatePlay()
{
	ObjectProcess::HitObject();
	gGameTimer.Update();
}

void PlayScene::UpdateClear()
{
}

void PlayScene::UpdateOver()
{
}

void PlayScene::UpdateResult()
{
	DrawString(200,200, "Result", 0xffffff);
}
