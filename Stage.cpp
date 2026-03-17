/// <summary>
/// ステージに関するクラス
/// </summary>
/// <author>H.suginunma</author>
#include "Stage.h"
#include"CsvReader.h"
#include "Player.h"
#include<assert.h>
namespace {
	const char IMAGE_SCALE = 16;
}
Stage::Stage()
{
	hImage= LoadGraph("data/Image/stage/stageGraph/TileImage.png");
	assert(hImage > 0);

	//マップの名前の読み込み
	CsvReader* nameCsv = new CsvReader("data/Image/stage/stageCSV/stageName.csv");
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
		std::string path = "data/Image/stage/stageCSV/" + mapName[i] + ".csv";
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
	
	//マップを初期化（チュートリアルに）
	currentNum = 0;
	nextNum = currentNum;
	if (!allMap.empty()) {
		map = allMap[currentNum];
	}

	//↓プレイヤーを指定の座標に出現させる
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 2) {
				new Player(x*IMAGE_SCALE, y*IMAGE_SCALE);
				break;
			}
			
		}
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	if (currentNum != nextNum)
	{
		map = allMap[nextNum];
		currentNum = nextNum;
	}
}

void Stage::Draw()
{
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 1) {
				DrawRectGraph(IMAGE_SCALE* x - scrollX, y * IMAGE_SCALE, 0,0, IMAGE_SCALE, IMAGE_SCALE, hImage, true);
			}
		}
	}
	//マップの名前入ってるかの確認用
	//for (int i = 0; i < mapName.size(); i++) {
	//	DrawFormatString(0, 30 * i, GetColor(255, 255, 255), "%s", mapName[i].c_str());
	//}
}
int Stage::HitWallRight(int x, int y)
{
	if (IsInWall(x, y)) {
		int dx = x % IMAGE_SCALE;
		return dx + 1.0f;
	}
	return 0;
}
int Stage::HitWallLeft(int x, int y)
{
	if (IsInWall(x, y)) {
		int dx = x % IMAGE_SCALE;
		return IMAGE_SCALE- dx;
	}
	return 0;
}

int Stage::HitFloor(int x, int y)
{
	if (IsInWall(x, y)) {
		int dy = y % IMAGE_SCALE;
		return dy + 1.0f;
	}
	return 0;
}

int Stage::HitCeiling(int x, int y)
{
	if (IsInWall(x, y)) {
		int dy = y % IMAGE_SCALE;
		return IMAGE_SCALE - dy;
	}
	return 0;
}

bool Stage::IsInWall(int x, int y)
{
	int map_y = y / IMAGE_SCALE;
	int map_x = x / IMAGE_SCALE;
	if (y < 0 || y >= map.size() * IMAGE_SCALE)
	{
		return false;
	}
	if (x < 0 || x >= map[map_y].size() * IMAGE_SCALE)
	{
		return false;
	}
	if (map[map_y][map_x] == 1) 
	{
		return true;
	}
	return false;
}

bool Stage::CanInteract(Vector2D pos)
{
	Vector2D portalPos;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			//ポータルの座標を獲得
			if (map[y][x] == 3) {
				//座標をマスの中心に変更
				portalPos.x = x * IMAGE_SCALE + IMAGE_SCALE / 2;
				portalPos.y = y * IMAGE_SCALE + IMAGE_SCALE / 2;
				break;
			}
		}
	}
	//プレイヤーのポジションを取得、中心に設定
	Vector2D pPos = { pos.x + IMAGE_SCALE / 2 ,pos.y + IMAGE_SCALE / 2 };
	//２つのベクトルの距離
	float dist = Math2D::Length(Math2D::Sub(pPos, portalPos));
	//どのくらい離れてたらインタラクトさせるか
	float interactLength = IMAGE_SCALE;
	if (dist <= interactLength)
	{
		return true;
	}
	return false;
}

void Stage::SetStage(std::string sName)
{
	for(int i = 0;i<mapName.size();i++)
	{
		if (sName == mapName[i])
		{
			nextNum = i;
			break;
		}
	}
}
