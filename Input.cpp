#include "Input.h"
#include "DxLib.h"

/// <summary>
/// キーボードとコントローラーの入力を管理する
/// </summary>
/// <author>H.suginuma</author>

namespace Input {
	//キーボード取得関連
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//キーバッファ (現フレーム)
	char keyBuffOld[KEY_MAX];	//1つ前のキーバッファ(前フレーム) 
	char key_down[KEY_MAX];		//押された瞬間 
	char key_up[KEY_MAX];		//離された瞬間 
	char Key_Keep[KEY_MAX];		//押しっぱなし

	//コントローラー取得関連
	const int PAD_MAX = 32;
	char padBuff[PAD_MAX];      //現フレーム
	char padBuffOld[PAD_MAX];   //前フレーム
	char pad_down[PAD_MAX];     //押された瞬間
	char pad_up[PAD_MAX];       //離された瞬間
	char pad_keep[PAD_MAX];     //押しっぱなし
	//スティックの値を保持する変数
	int stickX = 0, stickY = 0;

}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX);

	GetHitKeyStateAll(keyBuff);//全てのキーの状態を取得 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) Key_Keep[i]++;
		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//前フレームと現フレームのxor
		if (key_xor) Key_Keep[i] = 0;
		key_down[i] = key_xor & keyBuff[i];		//押された瞬間 = (現フレームとkey_xorのAND) 
		key_up[i] = key_xor & keyBuffOld[i];	//離された瞬間 = (前フレームとkey_xorのAND) 
	}

}

bool Input::IsKeyUP(int keyCode)
{
	return(key_up[keyCode]);

}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

int Input::IsKeepKeyDown(int keyCode)
{
	return(Key_Keep[keyCode]);
}

void Input::PadStateUpdate()
{
	memcpy_s(padBuffOld, sizeof(char) * PAD_MAX, padBuff, sizeof(char) * PAD_MAX);

	int inputBit = GetJoypadInputState(DX_INPUT_PAD1);

	for (int i = 0; i < PAD_MAX; i++)
	{
		//i番目のビットが立っているかチェック
		if (inputBit & (1 << i))
		{
			padBuff[i] = 1;
		}
		else
		{
			padBuff[i] = 0;
		}

		if (padBuff[i] && padBuffOld[i]) pad_keep[i]++;
		int pad_xor = padBuff[i] ^ padBuffOld[i];	//前フレームと現フレームのxor
		if (pad_xor) pad_keep[i] = 0;
		pad_down[i] = pad_xor & padBuff[i];		//押された瞬間 = (現フレームとkey_xorのAND) 
		pad_up[i] = pad_xor & padBuffOld[i];	//離された瞬間 = (前フレームとkey_xorのAND) 
	}

	GetJoypadAnalogInput(&stickX, &stickY, DX_INPUT_PAD1);
}

bool Input::IsPadUp(int padCode)
{
	return pad_up[padCode];
}

bool Input::IsPadDown(int padCode)
{
	return pad_down[padCode];
}

int Input::IsKeepPadDown(int padCode)
{
	return pad_keep[padCode];
}

Vector2D Input::GetStick()
{
	return Vector2D(Input::stickX,Input::stickY);
}