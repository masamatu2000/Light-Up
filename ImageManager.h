#pragma once
#include "GameObject.h"
#include<vector>
#include<string.h>
class Image : public GameObject
{
public:
	Image();
	~Image();
	/// <summary>
	/// キャラクターのグラフィックデータを取り出す
	/// </summary>
	/// <param name="Imname">ファイルの名前</param>
	/// <returns></returns>
	int ReturnImage(std::string Imname);
private:
	std::vector<int> images;
	std::vector<std::string> name;
};