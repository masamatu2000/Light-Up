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

	new Player(16,16);
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
			else if (map[y][x] == 2) {
				DrawRectGraph(IMAGE_SCALE*x - scrollX, y * IMAGE_SCALE,0,0,IMAGE_SCALE, IMAGE_SCALE, hImage, true);
			}
		}
	}
}
