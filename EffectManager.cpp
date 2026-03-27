#include "EffectManager.h"
#include "Player.h"
#include <assert.h>

namespace
{
	int patX;
	int patY;
	int patCounter;
	int timer;
}
Effect::Effect()
{
}

Effect::Effect(int x, int y)
{
	hImage = LoadGraph("data/image/character/aoi.png");
	position = Vector2D((float)x, (float)y);
	patX = 0;
	patY = 0;
	patCounter = 0;
	timer = 60;
	assert(hImage > 0);
	
}

Effect::~Effect()
{
}

void Effect::Update()
{

	//アニメーションをつける
	if (timer > 0)
	{
		timer = timer -(int)GetDeltaTime();
		patCounter++;
		patX = (patCounter / 4) % 4;
	}
	else if (timer == 0)
	{
		DestroyMe();
	}
}

void Effect::Draw()
{
	DrawRectGraph((int)position.x,(int) position.y, patX*64, patY*64, 64, 64, hImage, TRUE);
	//DrawBox(position.x, position.y, position.x + 16, position.y + 16, GetColor(0, 0, 255), TRUE);
}
