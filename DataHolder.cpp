#include "DataHolder.h"
/// <summary>
/// ステージとキャラクターの番号を保持する
/// </summary>
/// <author>H.suginuma</author>

DataHolder::DataHolder()
{
	DontDestroyOnSceneChange();
	stageNum = 1;
	playerNum = 1;
	isTutorialSkip = false;
	finishStageNum = 0;
	totalDestroyedEnemyNum = 0;
	fontSize = 10;
}

DataHolder::~DataHolder()
{
}
