#pragma once
#include "Object.h"
#include <vector>
class StageGraphic : public Object
{
public:
	StageGraphic();
	~StageGraphic();
	bool IsInWall(int x, int y);
private:
	void Update() override;
	void Draw() override;
private:
	std::vector<std::string> mapName; //マップの名前保存用
	std::vector<std::vector<std::vector<int>>> allMap; //全マップ保存用
	std::vector<std::vector<int>> map; //現在のマップを保存
};