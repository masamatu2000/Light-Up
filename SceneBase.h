#pragma once

/// <summary>
/// シーンの基底クラス
/// </summary>
/// <author>H.suginunma</author>

#include<list>
#include"GameObject.h"


class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Update() {}
	virtual void Draw() {}
};