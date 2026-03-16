#include "Stage.h"
#include"CsvReader.h"
#include "Player.h"
#include<assert.h>
namespace {
	const char IMAGE_SCALE = 16;
}
Stage::Stage()
{
	hImage= LoadGraph("data/Image/stage/TileImage.png");
	CsvReader* csv = new CsvReader("data/Image/stage/stage1-1.csv");
	int lines = csv->GetLines();//行数を取得
	map.resize(lines);//mapの行数を設定
	for (int y = 0; y < lines; y++) {//1行ずつ読む
		int colos = csv->GetColumns(y);//その行の桁数を取得
		map[y].resize(colos);//mapのその行の桁数を設定
		for (int x = 0; x < colos; x++) {
			map[y][x] = csv->GetInt(y, x);//mapに値を設定
		}
	}
	delete csv;
	assert(hImage > 0);
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
	if (y < 0 || y>map.size() * IMAGE_SCALE) {
		return false;
	}
	if (x < 0 || x>map[map_y].size() * IMAGE_SCALE) {
		return false;
	}
	if (map[map_y][map_x] == 1 || map[map_y][map_x] == 2) {
		return true;
	}
	return false;
}
