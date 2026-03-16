#include "Stage.h"
#include"CsvReader.h"
#include<assert.h>
Stage::Stage()
{
	hImage= LoadGraph("data/Image/stage/床イメージ.2.png");
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
				DrawRectGraph(16* x - scrollX, y * 16, 0, 16, 16, 16, hImage, true);
			}
			else if (map[y][x] == 2) {
				DrawRectGraph(16* x - scrollX, y * 16, 16, 16, 16, 16, hImage, true);
			}
		}
	}
}
