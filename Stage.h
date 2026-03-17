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
private:
	void Update() override;
	void Draw() override;
private:
	std::vector<std::string> mapName; //マップの名前保存用
	std::string mapReference; //マップの参照保存用
	std::vector<std::vector<int>> map;//CSV保存用
};