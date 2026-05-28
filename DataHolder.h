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
	void SetFinishStageNum(int num) { finishStageNum = num; }
	int GetFinishStageNum() { return finishStageNum; }
	void EnemyDestroyed() { totalDestroyedEnemyNum++; }
	int GetTotalDestroyedEnemyNum() { return totalDestroyedEnemyNum; }
	int stageNum;
	int playerNum;
	int finishStageNum;
	int totalDestroyedEnemyNum;
	//チュートリアルをスキップするか
	bool isTutorialSkip;
};