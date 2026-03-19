#pragma once
#include "GameObject.h"

/// <summary>
/// ステージとキャラクターの番号を保持する
/// </summary>
/// <author>H.suginuma</author>

class DataHolder : public GameObject
{
public:
	DataHolder();
	~DataHolder();

	int stageNum;
	int playerNum;
};