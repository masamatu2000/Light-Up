/// <summary>
/// SceneManagerから呼び出されてSceneを作成するクラス
/// SceneManagerを触らなくていいように、作成部分をここに分離しておく
/// 作るシーンは、enumで指定してもらうようにした
/// </summary>
/// <author>H.suginuma</author>
#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "TitleScene.h"
#include "PlayScene.h"

SceneBase* SceneFactory::Create(SCENE_NAME sceneName)
{
	switch (sceneName)
	{
	case SCENE_NAME::TITLE_SCENE:
		return new TitleScene();
		break;
	case SCENE_NAME::PLAY_SCENE:
		return new PlayScene();
		break;
	}
	MessageBox(NULL, ("次のシーンはありません\n"), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
