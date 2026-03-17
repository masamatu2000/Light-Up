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

	void SetStage(std::string sName);
private:
	void Update() override;
	void Draw() override;
private:
	std::vector<std::string> mapName; //マップの名前保存用
	std::vector<std::vector<std::vector<int>>> allMap; //全マップ保存用
	std::vector<std::vector<int>> map; //現在のマップを保存
	int currentNum; //マップの現在の番号を保存
	int nextNum; //次の番号を保存
};