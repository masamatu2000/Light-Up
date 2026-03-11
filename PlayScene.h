#pragma once
#include "SceneManager.h"

class PlayScene : Scene
{
private:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
};