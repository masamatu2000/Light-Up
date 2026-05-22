#include "UserInterface.h"
#include "Player.h"



UserInterface::UserInterface()
{
	Image* image = FindGameObject<Image>();
	hImage = image->ReturnImage("LiteUp_kuribou");
	hImage_2 = image->ReturnImage("LiteUp_yousei");
}

void UserInterface::Update()
{
}

void UserInterface::Draw()
{
	Player* pl = FindGameObject<Player>();
	DrawRotaGraph2(100, 100, 32, 64, 1, ((DX_PI * 2) * (0 - 50) / 200), hImage, TRUE);
	for (int i = 0;i < pl->GetCurse();i += 10)
	{
		DrawRotaGraph2(100, 100, 32, 64, 1, ((DX_PI * 2) * (i - 50) / 200), hImage, TRUE);
	}
	DrawRotaGraph2(100, 100, 32, 64, 1, ((DX_PI * 2) * (0 - 50) / 200), hImage_2, TRUE);
	for (int i = 0;i < pl->GetCurseLowerLimit();i+=10)
	{
		DrawRotaGraph2(100, 100, 32, 64, 1, ((DX_PI * 2) * (i - 50) / 200), hImage_2, TRUE);
	}

	if (0)
	{
		DrawBox(0, 0, 100, 50, GetColor(0, 0, 0), TRUE);
		DrawFormatString(0, 0, 0xffffff, "curseF%.0f", pl->GetCurse());
		DrawFormatString(0, 30, 0xffffff, "curseLLF%.0f", pl->GetCurseLowerLimit());
	}
}
