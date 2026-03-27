#pragma once
#include "PlayScene.h"
#include "Player.h"

class UserInterface : public Player
{
public:
	UserInterface();
	void Update() override;
	void Draw() override;
private:
	
};