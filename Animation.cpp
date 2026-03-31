#include "Animation.h"
/// <summary>
/// アニメーション時の背景の描画を管理するクラス
/// </summary>
/// <author>H.suginuma</author>

Animation::Animation()
{
	animeTimer = 0.0f;
	pat = 0;
	hImage = -1;
}

Animation::Animation(std::string name)
{
	animeTimer = 0.0f;
	pat = 0;
}

Animation::~Animation()
{
}

void Animation::Update()
{
}

void Animation::Draw()
{
}
