#pragma once
#include "Stage.h"
#include "GimmickType.h"

class Gimmick : Stage
{
public:
	Gimmick();
	~Gimmick();
private:
	void Update() override;
	void Draw() override;
private:
	GIMMICK_TYPE gimmiclType;
};