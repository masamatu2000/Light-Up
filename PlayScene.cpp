#include "PlayScene.h"
#include"Stage.h"
#include"Player.h"
#include "StageGraphic.h"
#include"ImageManager.h"
#include "UserInterface.h"
#include "Animation.h"

/// <summary>
/// ÉvÉåÉCíÜÇÃâÊñ ÇÃëJà⁄ÇÇ∑ÇÈ
/// </summary>
/// <author>H.suginuma</author>

namespace
{
	float dt = GetDeltaTime();
}

PlayScene::PlayScene()
{
	new Image();
	new Stage();
	state = State::START;
	time = 0;
	new StageGraphic();
	new UserInterface();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	SetFontSize(10);
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
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::TITLE_SCENE);
	}
	
}

void PlayScene::Draw()
{
	DrawString(100, 0, "PlayScene", 0xffffff);
	DrawString(100, 20, "Push [N]Key To Title", 0xffffff);
}

void PlayScene::UpdateStart()
{
	if (time < 1.0f) {
		time += dt;
		if (time >= 1.0f) {
			//1ïbÇΩÇ¡ÇΩÇÁPLAYÇ…à⁄çs
			state = State::PLAY;
			time = 0;
		}
	}
}

void PlayScene::UpdatePlay()
{
}

void PlayScene::UpdateClear()
{
}

void PlayScene::UpdateOver()
{
}

void PlayScene::UpdateResult()
{
}
