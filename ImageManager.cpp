#include "ImageManager.h"
#include"CsvReader.h"
Image::Image()
{
	CsvReader* csv = new CsvReader("ImageName.csv");
	int lines = csv->GetLines();//行数を取得
	Images.resize(lines);//mapの行数を設定
	for (int y = 0; y < lines; y++) {//1行ずつ読む
		int colos = csv->GetColumns(y);//その行の桁数を取得
		Images[y].resize(colos);//mapのその行の桁数を設定
		for (int x = 0; x < colos; x++) {
			Images[y][x] = csv->GetInt(y, x);//mapに値を設定
		}
	}
	delete csv;
}

Image::~Image()
{
}

int Image::ReturnImage(std::string Imname)
{
	int i = 0;
	int target = stoi(Imname);
	// Imagesは2次元配列なので、全ての値を探索する必要があります
	for (size_t y = 0; y < Images.size(); ++y) {
		for (size_t x = 0; x < Images[y].size(); ++x) {
			if (target == Images[y][x]) {
				return LoadGraph((const TCHAR*)Images[y][x]);
			}
		}
	}
	return 0;
}
