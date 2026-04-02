#include "Animation.h"
#include"Stage.h"
#include"ImageManager.h"
#include"Player.h"
/// <summary>
/// アニメーション時の背景の描画を管理するクラス
/// </summary>
/// <author>H.suginuma</author>

//スタートアニメーション用の定数
namespace Start
{
	//アニメーションの時間
	const float ANIME_TIME = 5.0f;
}
//クリアアニメーション用の定数
namespace Clear
{
	//プレイヤーの移動する距離（マス）X軸方向
	const int PLAYER_MOVE_X = 10 * IMAGE_SCALE;
	//アニメーションの時間
	const float ANIME_TIME = 10.0f;
}


Animation::Animation()
{
	animeTimer = 0.0f;
	patX = 0;
	patY = 0;
	playerImage = -1;
	corpseImage = -1;
}

Animation::Animation(Name name)
{
	animeName = name;
	animeTimer = 0.0f;
	patX = 0;
	patY = 0;
	switch (animeName)
	{
	case START:
		InitializeStart();
		break;
	case CLEAR:
		InitializeClear();
		break;
	}
}

Animation::~Animation()
{
}

void Animation::InitializeStart()
{
}

void Animation::InitializeClear()
{
	Stage* s = FindGameObject<Stage>();
	//アニメーション開始位置を取得
	position = s->GetAnimationPos();
	startPos = position;
	Image* image = FindGameObject<Image>();
	//プレイヤーの画像を取得
	playerImage = image->ReturnImage("player");
	//ボスの死体画像を取得
	//今はまだ画像がないので省略
}

void Animation::Update()
{
	switch (animeName)
	{
	case START:
		UpdateStart();
		break;
	case CLEAR:
		UpdateClear();
		break;
	}
}

void Animation::UpdateStart()
{
}

void Animation::UpdateClear()
{
	//アニメーションのレート
	float rate = animeTimer / Clear::ANIME_TIME;
	//プレイヤーを移動
	position.x = startPos.x + Clear::PLAYER_MOVE_X * rate;
	//スクロール処理
	Scroll();
	animeTimer += gDeltaTime;
	//アニメーションの終了処理
	if (animeTimer > Clear::ANIME_TIME)
	{
		DestroyMe();
		Player* p = FindGameObject<Player>();
		p->AnimationEnd();
	}
}

void Animation::Draw()
{
	switch (animeName)
	{
	case START:
		DrawStart();
		break;
	case CLEAR:
		DrawClear();
		break;
	}
}

void Animation::DrawStart()
{
}

void Animation::DrawClear()
{
	int x, y;
	x = (int)(position.x - Stage::scrollX);
	y = (int)(position.y - Stage::scrollY);
	DrawRectGraph(x, y, IMAGE_SCALE * patX, IMAGE_SCALE * patY, IMAGE_SCALE, IMAGE_SCALE, playerImage, TRUE);
	//DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, 0xffffff, TRUE);
}

void Animation::Scroll()
{
	Stage::scrollX = (int)(position.x - 100);
	Stage::scrollY = (int)(position.y - 100);
}