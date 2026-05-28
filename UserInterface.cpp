#include "UserInterface.h"
#include "Player.h"



UserInterface::UserInterface()
{
	SetDrawOrder(-1000000);
	Image* image = FindGameObject<Image>();
	hImage = image->ReturnImage("Hp1");
	hImage_2 = image->ReturnImage("Hp2");
	hImage_3 = image->ReturnImage("Hp3");
	hImage_4 = image->ReturnImage("Hp4");
}

void UserInterface::Update()
{
}

void UserInterface::Draw()
{
	Player* pl = FindGameObject<Player>();

	if (isDebug)
	{
		DrawBox(0, 0, 100, 50, GetColor(0, 0, 0), TRUE);
		DrawFormatString(0, 0, 0xffffff, "curseF%.0f", pl->GetCurse());
		DrawFormatString(0, 30, 0xffffff, "curseLLF%.0f", pl->GetCurseLowerLimit());
	}

	DrawGraph(10, 10, hImage_3, TRUE);
	for (int i = 0;i < pl->GetCurse();i ++)
	{
		DrawRotaGraph2(74, 78, 64, 64, 1, ((DX_PI * 2) * (i - 50) / 200), hImage, TRUE);
	}
	for (int i = 0;i < pl->GetCurseLowerLimit();i++)
	{
		DrawRotaGraph2(74, 78, 64, 64, 1, ((DX_PI * 2) * (i - 50) / 200), hImage_2, TRUE);
	}
	DrawGraph(10, 10,hImage_4, TRUE);
	DrawFormatString(40, 90, 0xffffff, "%d", pl->GetMainAttackRecast());
	DrawFormatString(70, 110, 0xffffff, "%d", pl->GetSubAttackRecast());
	DrawFormatString(100, 90, 0xffffff, "%d", pl->GetSupportRecast());
}
