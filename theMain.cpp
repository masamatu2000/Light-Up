#include "DxLib.h"
#include "globals.h"
#include "input.h"
#include"ObjectManager.h"
#include"SceneManager.h"
/// <summary>
/// main関数
/// スクリーン（ウィンドウ）の管理
/// </summary>
/// <author>H.suginuma</author>

namespace
{
	const int BGCOLOR[3] = {0, 0, 0}; // 背景色{ 255, 250, 205 }; // 背景色
	int crrTime;
	int prevTime;
	//最終的に何倍のサイズにするか
	//---画像を維持するために整数以外入れるな)---
	const int SCREEN_ZOOM = 4;
}


float gDeltaTime = 0.0f; // フレーム間の時間差

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0],BGCOLOR[1],BGCOLOR[2]);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}

void Initialize()
{
	ObjectManager::Initialize();
	SceneManager::Initialize();
}

void Update()
{
	ObjectManager::Update();
	SceneManager::Update();
}

void Draw()
{
	ObjectManager::Draw();
	SceneManager::Draw();
}

void Release()
{

}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	Initialize();

	//SCREEN_ZOOMに拡大するために仮想のスクリーンを作る
	int vWidth = WIN_WIDTH / SCREEN_ZOOM;
	int vHeight = WIN_HEIGHT / SCREEN_ZOOM;
	int virtualScreen = MakeScreen(vWidth, vHeight, FALSE);

	while (true)
	{
		//仮想画面に描画
		SetDrawScreen(virtualScreen);
		ClearDrawScreen();

		Input::KeyStateUpdate(); // キー入力の状態を更新

		crrTime = GetNowCount(); // 現在の時間を取得
		// 前回の時間との差分を計算
		float deltaTime = (crrTime - prevTime) / 1000.0f; // 秒単位に変換
		gDeltaTime = deltaTime; // グローバル変数に保存

		//ここにやりたい処理を書く
		Update();
		Draw();

		//本番用の画面に
		SetDrawScreen(DX_SCREEN_BACK);
		//ドット維持用
		SetDrawMode(DX_DRAWMODE_NEAREST);
		//FHDサイズに画像として拡大
		DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, virtualScreen, FALSE);

		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // 現在の時間を前回の時間として保存

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	Release();
	return 0;
}