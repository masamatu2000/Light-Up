/// <summary>
/// ステージに関するクラス
/// </summary>
/// <author>H.suginunma</author>
#include "Stage.h"
#include"CsvReader.h"
#include "Player.h"
#include "Enemy.h"
#include"Boss.h"
#include<assert.h>
#include"DataHolder.h"
#include"Gimmick.h"
namespace {
	//チュートリアル、裏ステ含めた６ステージ
	const int STAGE_MAX = 6;
	//それぞれのCSV番号
	const int PLAYER_CSV_NUM = 2;
	const int ENEMY01_CSV_NUM = 10;
	const int ENEMY02_CSV_NUM = 11;
	const int BOSS01_CSV_NUM = 21;
}

int Stage::scrollX = 0;
int Stage::scrollY = 0;
int Stage::mapBottom = 0;
int Stage::mapTop = 0;
int Stage::mapLeft = 0;
int Stage::mapRight = 0;

Stage::Stage()
{
	//hImage= LoadGraph("data/Image/stage/stageGraph/TileImage.png");
	//assert(hImage > 0);

	//ステージ背景の描画の為の画像読み込み
	hImage = LoadGraph("data/Image/stage/BG/BG.png");

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
	//スクロール、上限値の設定
	SetScroll();
	//↓プレイヤーを指定の座標に出現させる
	SetPlayer();
	//敵を生成
	SetEnemy_Boss();

	//マップをチュートリアルに
	currentStage = 0;

	//ボスを倒してないことに
	isBossDefeated.clear();
	isBossDefeated.resize(STAGE_MAX, false);
}

Stage::~Stage()
{
}

void Stage::Update()
{
	if (currentNum != nextNum)
	{
		auto gmmick = FindGameObjects<Gimmick>();
		for (auto gm : gmmick)
		{
			if (gm->GetGimmicType() == GIMMICK_TYPE::Corpse)
			{
				gm->DestroyMe();
			}
		}
		auto enemy = FindGameObjects<Enemy>();
		for (auto e : enemy) {
			e->DestroyMe();
		}
		Boss* boss = FindGameObject<Boss>();
		if (boss != nullptr) {
			boss->DestroyMe();
		}
		map = allMap[nextNum];
		currentNum = nextNum;
		//スクロール、上限値を設定
		SetScroll();
		//プレイヤーの位置を新しいマップの初期位置に移動
		SetPlayerPosition();
		
		SetEnemy_Boss();

		//デバッグ用
		//ボスがいるマップに行ったらtrueに
		//本来はボスを撃破したらtrueに
		DataHolder* dh = FindGameObject<DataHolder>();
		isBossDefeated[currentStage] = false;
		for (int y = 0; y < map.size(); y++) {
			for (int x = 0; x < map[y].size(); x++) {
				//ボスのCSV番号の21にで判別
				if (map[y][x] == 21) {
					isBossDefeated[currentStage] = true;
					break;
				}
			}
		}
		
	}
}

void Stage::Draw()
{
	//ステージの背景の描画(仮)
	DrawGraph(0 - Stage::scrollX, 0 - Stage::scrollY,hImage,true);

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 1) {
				//DrawRectGraph(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, 0, 0, IMAGE_SCALE, IMAGE_SCALE, hImage, true);
				DrawBox(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, IMAGE_SCALE * x - Stage::scrollX + IMAGE_SCALE, y * IMAGE_SCALE - Stage::scrollY + IMAGE_SCALE,GetColor(0,255,255), false);
			}
			if (map[y][x] == 3) {
				//DrawRectGraph(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, 0, 0, IMAGE_SCALE, IMAGE_SCALE, hImage, true);
				DrawBox(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, IMAGE_SCALE * x - Stage::scrollX + IMAGE_SCALE, y * IMAGE_SCALE - Stage::scrollY + IMAGE_SCALE, GetColor(255, 255, 0), false);
			}
			if (map[y][x] == 4) {
				//DrawRectGraph(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, 0, 0, IMAGE_SCALE, IMAGE_SCALE, hImage, true);
				DrawBox(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, IMAGE_SCALE * x - Stage::scrollX + IMAGE_SCALE, y * IMAGE_SCALE - Stage::scrollY + IMAGE_SCALE, GetColor(0, 255, 0), false);
			}
		}
	}
	
	//現在のマップ確認用
	DrawFormatString(0, 100, 0xffff00, "%s", mapName[currentNum].c_str());
	DrawFormatString(0, 120, 0x0000ff, "%d %d %d %d %d %d",
		(int)isBossDefeated[0], 
		(int)isBossDefeated[1],
		(int)isBossDefeated[2],
		(int)isBossDefeated[3],
		(int)isBossDefeated[4],
		(int)isBossDefeated[5]
	);
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

bool Stage::CanChangeStage(Vector2D pos, std::string direction)
{
	if (direction == "next")
	{
		//nextに行けるか調べる
		//CSV上のnextポータルを表す3で検索
		return CanInteract(pos, 3);
	}
	else if (direction == "previous")
	{
		//previousに行けるか調べる
		//CSV上のpreviousポータルを表す4で検索
		return CanInteract(pos, 4);
	}
	return false;
}

bool Stage::CanInteract(Vector2D pos, int findNum)
{
	Vector2D portalPos;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			//ポータルの座標を獲得
			if (map[y][x] == findNum) {
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

void Stage::NextStage()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	//全ボス倒してたらステージ5に
	if (IsBossComplete())
	{
		SetStage("stage5-1");
		dh->stageNum = 5;
		currentStage = dh->stageNum;
		isBossDefeated.clear();
		isBossDefeated.resize(STAGE_MAX, false);
	}
	//今のステージのボスを倒したら次のステージに
	else if (isBossDefeated[currentStage])
	{
		if (currentStage == 5)
		{
			//全ボス倒したらタイトルに
			SceneManager::ChangeScene(SCENE_NAME::TITLE_SCENE);
		}
		else if (currentStage != 5)
		{
			std::string name = "stage" + std::to_string(dh->stageNum) + "-1";
			SetStage(name);
			currentStage = dh->stageNum;
			dh->stageNum += 1;
			if (dh->stageNum > STAGE_MAX - 2)
			{
				dh->stageNum = 1;
			}
		}
	}
	//そのステージの次のセクションに
	else
	{
		if (currentNum + 1 > mapName.size() - 1)
		{
			return;
		}
		SetStage(mapName[currentNum + 1]);
	}
	isNext = true; //次に進む
}

void Stage::PreviousStage()
{
	if (currentNum - 1 < 0)
	{
		return;
	}
	SetStage(mapName[currentNum - 1]);
	isNext = false; //前に戻る
}

bool Stage::IsBossComplete()
{
	//１体でも残ってたらfalseを返す
	for (int i = 0; i < STAGE_MAX -1; i++)
	{
		if (!isBossDefeated[i])
		{
			return false;
		}
	}
	return true;
}

bool Stage::IsCorpse(const Vector2D& pos)
{
	auto gmmick = FindGameObjects<Gimmick>();
	for (auto gm : gmmick)
	{
		if (gm->GetGimmicType() == GIMMICK_TYPE::Corpse) 
		{
			Vector2D gpos = gm->GetPosition();
			Vector2D dist = {abs(gpos.x-pos.x),abs(gpos.y-pos.y)};
			if (dist.x / IMAGE_SCALE <= 1 && dist.y / IMAGE_SCALE <= 1) {
				return true;
			}
		}
	}
	
	return false;
}

void Stage::CreateCorpse(const Vector2D& pos)
{
	new Gimmick(pos, GIMMICK_TYPE::Corpse);
}

void Stage::SetScroll()
{
	Stage::mapBottom = map.size() * IMAGE_SCALE - (WIN_HEIGHT / SCREEN_ZOOM);
	Stage::mapTop = 0;
	Stage::mapLeft = 0;
	Stage::mapRight = map[0].size() * IMAGE_SCALE - (WIN_WIDTH / SCREEN_ZOOM);

	Stage::scrollX = Stage::mapLeft;
	Stage::scrollY = Stage::mapBottom;
}

void Stage::SetPlayer()
{
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == PLAYER_CSV_NUM) {
				new Player(x * IMAGE_SCALE, y * IMAGE_SCALE);
				break;
			}

		}
	}
}

void Stage::SetPlayerPosition()
{
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			int findNum;
			if (isNext)
			{
				findNum = 4;
			}
			else if (!isNext)
			{
				findNum = 3;
			}
			//階段と同じ場所に
			if (map[y][x] == findNum) {
				Player* p = FindGameObject<Player>();
				p->SetPosition({ (float)x * IMAGE_SCALE, (float)y * IMAGE_SCALE });
				break;
			}

		}
	}
}

void Stage::SetEnemy_Boss()
{
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == ENEMY01_CSV_NUM) {
				new Enemy(Vector2D(x * IMAGE_SCALE, y * IMAGE_SCALE),ENEMY_NUMBER::Enemy01);
				break;
			}
			if (map[y][x] == ENEMY02_CSV_NUM) {
				new Enemy(Vector2D(x * IMAGE_SCALE, y * IMAGE_SCALE), ENEMY_NUMBER::Enemy02);
				break;
			}
			if (map[y][x] == BOSS01_CSV_NUM)
			{
				new Boss(Vector2D(x * IMAGE_SCALE, y * IMAGE_SCALE), BOSS_NUMBER::BOSS01);
				break;
			}

		}
	}
}
