#include "UserInterface.h"
#include "Player.h"



UserInterface::UserInterface()
{

}

void UserInterface::Update()
{
}

void UserInterface::Draw()
{
	Player* pl = FindGameObject<Player>();
	DrawBox(0, 0, 100, 50, GetColor(0, 0, 0), TRUE);

	DrawFormatString(0, 0, 0xffffff, "curseF%f", pl->GetCurse());
	DrawFormatString(0, 30, 0xffffff, "curseLLF%.0f", pl->GetCurseLowerLimit());
}
