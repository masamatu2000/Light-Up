/// <summary>
/// ステージに関するクラス
/// </summary>
/// <author>H.suginunma</author>
#pragma once
#include "Object.h"
#include <vector>
class Stage : public Object
{
public:
	Stage();
	~Stage();
	int HitWallRight(int x, int y);
	int HitWallLeft(int x, int y);
	int HitFloor(int x, int y);
	int HitCeiling(int x, int y);
	bool IsInWall(int x, int y);
	//プレイヤーが引数で指定した方向に行けるか
	bool CanChangeStage(Vector2D pos, std::string direction);
	//プレイヤーのポジションを引数として与えることで距離を測り、インタラクトできるかを返す
	bool CanInteract(Vector2D pos, int findNum);
	//ステージ名（stage0-1など）を引数に与えるとこでステージが変わる
	void SetStage(std::string sName);
	//次のステージに移行させる関数（プレイヤーが呼び出す）
	void NextStage();
	//前のステージに移行させる関数
	void PreviousStage();

	//スクロール用変数
	static int scrollX;
	static int scrollY;
	static int mapBottom;

private:
	void Update() override;
	void Draw() override;
private:
	std::vector<std::string> mapName; //マップの名前保存用
	std::vector<std::vector<std::vector<int>>> allMap; //全マップ保存用
	std::vector<std::vector<int>> map; //現在のマップを保存
	int currentNum; //マップの現在の番号を保存
	int nextNum; //次のマップ番号
	bool isNext; //進むのかどうか
};