#include "StageGraphic.h"
#include "Stage.h"
#include"CsvReader.h"
#include "Player.h"
#include "Enemy.h"
#include<assert.h>

namespace {
	const char IMAGE_SCALE = 16;
	int currentNum;
	int nextNum;
}

StageGraphic::StageGraphic()
{
	hImage = LoadGraph("data/Image/stage/stageGraph/stageTexture.png");
	assert(hImage > 0);

	//マップの名前の読み込み
	CsvReader* nameCsv = new CsvReader("data/Image/stage/stageGraph/stageTectureName.csv");
	int nLines = nameCsv->GetLines();//行数を取得
	mapName.resize(nLines);//mapの行数を設定
	for (int i = 0; i < nLines; i++) {//1行ずつ読む
		//改行を消すため一時保存
		std::string name = nameCsv->GetString(i, 0);

		//改行がある場合
		if (!name.empty() && name.back() == '\r' || !name.empty() && name.back() == '\n')
		{
			name.pop_back();
		}

		mapName[i] = name;
	}
	delete nameCsv;

	//全マップの読み込み
	for (int i = 0; i < mapName.size(); i++) {
		//マップの参照
		std::string path = "data/Image/stage/stageGraph/" + mapName[i] + ".csv";
		//std::string path = "data/Image/stage/stageCSV/stage0-1.csv";

		CsvReader* stageCsv = new CsvReader(path.c_str());

		//マップ情報保持用配列
		std::vector<std::vector<int>> oneMap;
		int sLines = stageCsv->GetLines();//行数を取得

		if (sLines == 0) {
			// ここで止まる場合は、ファイル名（path）が間違っています
			assert(false && "Map file not found or empty!");
		}

		oneMap.resize(sLines);//mapの行数を設定
		for (int y = 0; y < sLines; y++) {//1行ずつ読む
			int colos = stageCsv->GetColumns(y);//その行の桁数を取得
			oneMap[y].resize(colos);//mapのその行の桁数を設定
			for (int x = 0; x < colos; x++) {
				oneMap[y][x] = stageCsv->GetInt(y, x);//mapに値を設定
			}
		}
		allMap.push_back(oneMap);
		delete stageCsv;
	}

	Stage* stage = FindGameObject<Stage>();
	currentNum = stage->GetCurrentNum();
	nextNum = stage->GetNextNum();
	currentNum = 0;
	nextNum = currentNum;
	if (!allMap.empty()) {
		map = allMap[currentNum];
	}
	IsNextData = true;
}

StageGraphic::~StageGraphic()
{

}

void StageGraphic::Update()
{

	Stage* stage = FindGameObject<Stage>();
	currentNum = stage->GetCurrentNum();
	nextNum = stage->GetNextNum();
	if (nextNum < allMap.size())
	{
		IsNextData = true;
		if (currentNum != nextNum)
		{
			map = allMap[nextNum];
			currentNum = nextNum;
		}
	}
	else
	{
		IsNextData = false;
	}
	//DrawFormatString(10, 60, 0xffffff, "C:%d N:%d", currentNum, nextNum);
}

void StageGraphic::Draw()
{
	if (IsNextData)
	{
		for (int y = 0; y < map.size(); y++) {
			for (int x = 0; x < map[y].size(); x++) {
				for (int B = 0; B <= 27; B++)
				{
					if (map[y][x] == B) {
						DrawRectGraph(IMAGE_SCALE * x - Stage::scrollX - IMAGE_SCALE,
							y * IMAGE_SCALE - Stage::scrollY - IMAGE_SCALE,
							(B%7) * IMAGE_SCALE,
							(B/7) * IMAGE_SCALE,
							IMAGE_SCALE,
							IMAGE_SCALE,
							hImage, true);
						break;
					}
				}
			}
		}
	}
}