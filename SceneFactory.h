#pragma once
/// <summary>
/// SceneManagerから呼び出されてSceneを作成するクラス
/// SceneManagerを触らなくていいように、作成部分をここに分離しておく
/// 作るシーンは、enumで指定してもらうようにした
/// </summary>
#include"SceneBase.h"

class SceneFactory
{
public:
	/// <summary>
	/// 指定されたシーンを作成する
	/// </summary>
	/// <param name="name">シーンの名称</param>
	/// <returns>作成したインスタンス</returns>
	SceneBase* Create(SCENE_NAME sceneName);
};