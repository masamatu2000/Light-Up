/// <summary>
/// SceneManagerから呼び出されてSceneを作成するクラス
/// SceneManagerを触らなくていいように、作成部分をここに分離しておく
/// 作るシーンは、enumで指定してもらうようにした
/// </summary>
/// <author>H.suginuma</author>
#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include"BootScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include"SelectScene.h"
#include "ResultScene.h"
#include"GameOver.h"
#include"ClearScene.h"
SceneBase* SceneFactory::Create(SCENE_NAME sceneName)
{
	switch (sceneName)
	{
	case SCENE_NAME::BOOT_SCENE:
		return new BootScene();
		break;
	case SCENE_NAME::TITLE_SCENE:
		return new TitleScene();
		break;
	case SCENE_NAME::SELECT_SCENE:
		return new SelectScene();
		break;
	case SCENE_NAME::PLAY_SCENE:
		return new PlayScene();
		break;
	case SCENE_NAME::RESULT_SCENE:
		return new ResultScene();
		break;
	case SCENE_NAME::GAMEOVER_SCENE:
		return new GameOver();
		break;
	case SCENE_NAME::CLEAR_SCENE:
		return new ClearScene();
		break;
	}
	MessageBox(NULL, ("次のシーンはありません\n"), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
