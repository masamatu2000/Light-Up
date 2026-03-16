#pragma once
#include "Object.h"
#include <vector>
class Stage : Object
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
	std::vector<std::vector<int>> map;//CSV•Û‘¶—p
};