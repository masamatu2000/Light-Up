#pragma once
#include"Math2D.h"

/// <summary>
/// キーボードとコントローラーの入力を管理する
/// </summary>
/// <author>H.suginuma</author>

namespace Input {
	//キーボード取得関連
	void KeyStateUpdate();
	bool IsKeyUP(int keyCode);
	bool IsKeyDown(int keyCode);
	int IsKeepKeyDown(int keyCode);

	//コントローラー
	void PadStateUpdate();
	bool IsPadUp(int padCode);
	bool IsPadDown(int padCode);
	int IsKeepPadDown(int padCode);
	//アナログスティックの数値取得用
	Vector2D GetStick();
}

enum Pad
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
	A,
	B,
	X,
	Y,
	RB,
	LB,
	VIEW,
	OPTION
};