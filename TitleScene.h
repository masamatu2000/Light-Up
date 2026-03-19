#pragma once
#include "SceneBase.h"

/// <summary>
/// ƒ^ƒCƒgƒ‹‰æ–Ê
/// </summary>
/// <author>H.suginuma</author>

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
};