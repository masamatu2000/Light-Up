#pragma once
#include "Object.h"
#include <vector>
class Stage : Object
{
public:
	Stage();
	~Stage();
private:
	void Update() override;
	void Draw() override;
private:
	std::vector<std::vector<int>> map;
};