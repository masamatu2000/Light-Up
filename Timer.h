#pragma once
#include<functional>

//フレーム間時間
extern float gDeltaTime;

/// <summary>
/// 全体の時間を管理する
/// </summary>
namespace Time
{
	/// <summary>
	/// フレーム間時間を取得
	/// </summary>
	/// <returns>フレーム間時間</returns>
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
}

/// <summary>
/// 時間を管理する構造体
/// </summary>
struct Timer
{
	int counter = 0;
	int animCounter = 0;
	float timer = 0.0f;
	bool isStop = false;
	/// <summary>
	/// タイマーの値を取得する
	/// </summary>
	/// <returns>現在の経過時間</returns>
	float GetTimer() { return timer; }
	/// <summary>
	/// タイマーの更新
	/// </summary>
	void Update() {
		if (isStop)return;
		counter++;
		if (counter % 10 == 0)animCounter++;
		if (animCounter > 256)animCounter = 0;
		timer += Time::GetDeltaTime();
	}
	/// <summary>
	/// 指定した時間間隔ごとにtrueを返す
	/// </summary>
	/// <param name="interval">時間間隔</param>
	/// <returns>時間間隔を超えた瞬間にtrue</returns>
	bool IsEvery(float interval = 1.0f)
	{
		float dt = Time::GetDeltaTime();
		float prevTime = timer - dt;

		//前回の時間と今回の時間でintervalを跨いでいるか
		int currentCount = static_cast<int>(timer / interval);
		int prevCount = static_cast<int>(prevTime / interval);
		return currentCount > prevCount;
	}
	/// <summary>
	/// 指定したフレーム間隔ごとにtrueを返す
	/// </summary>
	/// <param name="interval">フレーム間隔</param>
	/// <returns>フレーム間隔を超えた瞬間にtrue</returns>
	bool IsEvery(int interval = 1)
	{
		//int prevCount = counter--;

		////前回の時間と今回の時間でintervalを跨いでいるか
		//int currentCount = static_cast<int>(counter / interval);
		//int prevCount = static_cast<int>(prevCount / interval);
		//return currentCount > prevCount;

		return (counter % interval == 0);
	}
	/// <summary>
	/// 指定した時間を超えた瞬間にtrueを返す
	/// </summary>
	/// <param name="sec">指定時間</param>
	/// <returns>時間を超えた瞬間にtrue</returns>
	bool isExpired(float sec)
	{
		float dt = Time::GetDeltaTime();
		float prevTime = timer - dt;

		//前回の時間と今回の時間でtimeを跨いでいるか
		return (prevTime < sec) && (sec <= timer);
	}
	/// <summary>
	/// 指定したフレームを超えた瞬間にtrueを返す
	/// </summary>
	/// <param name="frame">フレーム時間</param>
	/// <returns>フレーム時間を超えた瞬間にtrue</returns>
	bool isExpired(int frame)
	{
		float prevCount = counter--;

		//前回の時間と今回の時間でtimeを跨いでいるか
		return (prevCount < frame) && (frame <= counter);
	}
	/// <summary>
	/// タイマーを停止
	/// </summary>
	void Stop()
	{
		isStop = true;
	}
	/// <summary>
	/// タイマーを開始
	/// </summary>
	void Start()
	{
		isStop = false;
	}
	/// <summary>
	/// 開始、停止を切り替え
	/// </summary>
	void Switch()
	{
		if (isStop)isStop = false;
		else isStop = true;
	}
	/// <summary>
	/// 停止しているか
	/// </summary>
	/// <returns>停止していればtrue</returns>
	bool IsStop()
	{
		return isStop;
	}
	/// <summary>
	/// ループアニメーション用のカウンター
	/// </summary>
	/// <param name="limit">アニメーションの種類</param>
	/// <returns>アニメーション番号</returns>
	int LoopAnimCounter(int limit)
	{
		return animCounter % limit;
	}
};

//ゲーム全体のタイマー
extern Timer gGameTimer;