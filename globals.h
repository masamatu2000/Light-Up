#pragma once

//XGA SIZE
const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
//最終的に何倍のサイズにするか
//---画像を維持するために整数以外入れるな)---
//縦に１０マスくらいだとZOOMは3（１１．２５マスくらい）
const int SCREEN_ZOOM = 4;
const char IMAGE_SCALE = 32;
const char CHARACTER_IMAGE_SCALE = 64;

//重力
const float GRAVITY = 9.8f * 60 * 2;

extern float gDeltaTime; // フレーム間の時間差

inline float GetDeltaTime()
{
	if (gDeltaTime < 0.1f)
	{
		return gDeltaTime;
	}
	else
	{
		return 1 / 60;
	}
}