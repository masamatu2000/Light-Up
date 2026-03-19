#include "PlayScene.h"
#include"Stage.h"
#include"Player.h"

/// <summary>
/// ƒvƒŒƒC’†‚Ì‰æ–Ê‚Ì‘JˆÚ‚ğ‚·‚é
/// </summary>
/// <author>H.suginuma</author>

namespace
{
	float dt = GetDeltaTime();
}

PlayScene::PlayScene()
{
	new Stage();
	state = State::START;
	time = 0;
}

PlayScene::~PlayScene()
{
	switch (state)
	{
	case START :
	{
		if (time < 1.0f) {
			time += dt;
			if (time >= 1.0f) {
				//1•b‚½‚Á‚½‚çPLAY‚ÉˆÚs
				state = State::PLAY;
			}
		}
		break;
	}
	case PLAY :
	{
		break;
	}
	case CLEAR :
	{
		break;
	}
	case OVER :
	{
		break;
	}
	case END :
	{
		break;
	}
	}
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
