#include "EffectManager.h"
#include "Player.h"
#include "CsvReader.h"
#include <assert.h>
#include "Stage.h"
#include "Slash.h"

namespace
{
	int patX;
	int patY;
	int patCounter;
	float timer;
	std::vector<int> images;
	std::vector<std::string>name;
}
Effect::Effect()
{
}

Effect::Effect(int x, int y)
{

	CsvReader* csv = new CsvReader("data/Image/effect/Effect.csv");
	int lines = csv->GetLines();//エフェクト用の行数を取得
	images.clear();
	images.resize(lines);
	name.clear();
	name.resize(lines);
	for (int y = 0;y < lines;y++)//1行ずつ読み込んでいる
	{
		//改行を消すために一時保存する
		std::string str = csv->GetString(y, 0);

		//改行がある場合
		if (!str.empty() && str.back() == '\r' || !str.empty() && str.back() == '\n')
		{
			str.pop_back();
		}
		name[y] = str;

		std::string path = "data/Image/Effect/" + name[y] + ".png";
		images[y] = LoadGraph(path.c_str());
		
	}
	delete csv;

	position = Vector2D((float)x, (float)y-18);
	patX = 0;
	patY = 0;
	patCounter = 0;
	timer = 1.0f;//何フレーム動き続けるか
}

Effect::~Effect()
{
}

void Effect::Update()
{

	//アニメーションをつける
	timer = timer - GetDeltaTime();
	if (timer > 0)
	{
		patCounter++;
		patX = (patCounter / 5);
	}
	if (patX > 6)
	{
		DestroyMe();

	}
}

void Effect::Draw()
{


	float x = position.x - Stage::scrollX;
	float y = position.y - Stage::GetScrollY();


	DrawRectGraph(x,y, patX * 64, patY * 64, 64, 64, images[LiteUp_], TRUE);//スラッシュのエフェクト描画
	//DrawBox(position.x, position.y, position.x + 16, position.y + 16, GetColor(0, 0, 255), TRUE);
}
