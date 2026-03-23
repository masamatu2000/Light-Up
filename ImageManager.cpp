#include "ImageManager.h"
#include"CsvReader.h"
Image::Image()
{
	CsvReader* csv = new CsvReader("data/Image/character/ImageName.csv");
	int lines = csv->GetLines();//行数を取得
	images.clear();
	images.resize(lines);//mapの行数を設定
	name.clear();
	name.resize(lines);
	for (int y = 0; y < lines; y++) {//1行ずつ読む
		//改行を消すため一時保存
		std::string str = csv->GetString(y,0);

		//改行がある場合
		if (!str.empty() && str.back() == '\r' || !str.empty() && str.back() == '\n')
		{
			str.pop_back();
		}

		name[y] = str;

		std::string path = "data/Image/character/"+ name[y] + ".png";
		images[y] = LoadGraph(path.c_str());
	}
	delete csv;
}

Image::~Image()
{
}

int Image::ReturnImage(std::string Imname)
{
	// imagesは2次元配列なので、全ての値を探索する必要があります
	for (int y = 0; y < name.size(); y++) {
		if (Imname == name[y]) {
			return images[y];
		}
	}
	return -1;
}
