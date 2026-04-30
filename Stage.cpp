/// <summary>
/// ステージに関するクラス
/// </summary>
/// <author>H.suginunma</author>
#include "Stage.h"
#include"CsvReader.h"
#include "Player.h"
//敵用のクラスインクルード
#include "Enemy.h"
#include"Kuriboh.h"
#include"Fairy.h"
#include"Turret.h"
#include"Bomber.h"
//ボス用のクラスインクルード
#include"Boss.h"
#include<assert.h>
#include"DataHolder.h"
#include"Gimmick.h"
#include "Santana.h"
#include "SoundManager.h"

namespace {
	//チュートリアル、裏ステ含めた６ステージ
	const int STAGE_MAX = 6;
	//それぞれのCSV番号
	const int PLAYER_CSV_NUM = 2;
	const int NEXTPORTAL_CSV_NUM = 3;
	const int PREVIOUSPORTAL_CSV_NUM = 4;
	const int PLAYERSPAWN_CSV_NUM = 5;
	const int KURIBOH_CSV_NUM = 10;
	const int FAIRY_CSV_NUM = 11;
	const int TURRET_CSV_NUM = 12;
	const int BOMBER_CSV_NUM = 13;
	const int BOSS01_CSV_NUM = 21;

	//サウンド再生用に仮でおいておく
	Sound* s = nullptr;
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
	BgImage.clear();
	BgImage.push_back(LoadGraph("data/Image/stage/BG/BG_slum.png"));
	BgImage.push_back(LoadGraph("data/Image/stage/BG/BG_library.png"));
	BgImage.push_back(LoadGraph("data/Image/stage/BG/BG_slum.png"));
	BgImage.push_back(LoadGraph("data/Image/stage/BG/BG_slum.png"));
	BgImage.push_back(LoadGraph("data/Image/stage/BG/BG_slum.png"));
	BgImage.push_back(LoadGraph("data/Image/stage/BG/BG_slum.png"));

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
	
	//マップを初期化
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

	isStartSection = true;
	isBossSection = false;
	direction = Direction::NEXT;

	s = new Sound();
}

Stage::~Stage()
{
}

void Stage::Update()
{
	if (currentNum != nextNum)
	{
		DeleteObjects();
		map = allMap[nextNum];
		currentNum = nextNum;
		isBossSection = false;
		//スクロール、上限値を設定
		SetScroll();
		//敵とボスを生成
		SetEnemy_Boss();
		//プレイヤーの位置を新しいマップの初期位置に移動
		SetPlayerPosition();
	}
	if (((Input::IsKeyDown(KEY_INPUT_O)) || (Input::IsPadDown(Pad::OPTION))))
	{
		NextSection();
	}
}

void Stage::Draw()
{
	//ステージの背景の描画
	if (currentNum <= 3)
	{
		DrawGraph((int)(0 - Stage::scrollX), (int)(0 - Stage::GetScrollY()), BgImage[0], true);
	}
	else if(currentNum <= 8)
	{
		DrawGraph((int)(0 - Stage::scrollX), (int)(0 - Stage::GetScrollY()), BgImage[1], true);
	}
	else if (currentNum <= 16)
	{
		DrawGraph((int)(0 - Stage::scrollX), (int)(0 - Stage::GetScrollY()), BgImage[2], true);
	}
	else if (currentNum <= 22)
	{
		DrawGraph((int)(0 - Stage::scrollX), (int)(0 - Stage::GetScrollY()), BgImage[3], true);
	}
	else if (currentNum <= 28)
	{
		DrawGraph((int)(0 - Stage::scrollX), (int)(0 - Stage::GetScrollY()), BgImage[4], true);
	}
	else if (currentNum <= 34)
	{
		DrawGraph((int)(0 - Stage::scrollX), (int)(0 - Stage::GetScrollY()), BgImage[5], true);
	}

	//BGMの再生
	if (currentNum <= 2)
	{
		s->BgmPlay("starSleep");
	}
	else
	{
		s->BgmPlay("neverEndsNight");
	}

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			int posX = IMAGE_SCALE * x - Stage::scrollX;
			int posY = (int)(IMAGE_SCALE * y - Stage::GetScrollY());
			if (map[y][x] == 1) {
				//DrawRectGraph(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, 0, 0, IMAGE_SCALE, IMAGE_SCALE, hImage, true);
				DrawBox(posX,posY,posX + IMAGE_SCALE,posY + IMAGE_SCALE,GetColor(0,255,255), false);
			}
			if (map[y][x] == 3) {
				//DrawRectGraph(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, 0, 0, IMAGE_SCALE, IMAGE_SCALE, hImage, true);
				DrawBox(posX, posY, posX + IMAGE_SCALE, posY + IMAGE_SCALE, GetColor(255, 255, 0), false);
			}
			if (map[y][x] == 4) {
				//DrawRectGraph(IMAGE_SCALE * x - Stage::scrollX, y * IMAGE_SCALE - Stage::scrollY, 0, 0, IMAGE_SCALE, IMAGE_SCALE, hImage, true);
				DrawBox(posX, posY, posX + IMAGE_SCALE, posY + IMAGE_SCALE, GetColor(0, 255, 0), false);
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
		return dx + 1;
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
		return dy + 1;
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
				portalPos.x = (float)(x * IMAGE_SCALE + IMAGE_SCALE / 2);
				portalPos.y = (float)(y * IMAGE_SCALE + IMAGE_SCALE / 2);
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

void Stage::NextSection()
{
	//サウンドの再生を止める関数
	s->SoundStop();

	direction = Direction::NEXT;
	isStartSection = false;
	//ボスがいなければ次のセクションに
	if (!isBossSection)
	{
		if (currentNum + 1 <= mapName.size() - 1)
		{
			SetStage(mapName[currentNum + 1]);
		}
	}
	//全ボス倒してたら最終ステージに
	else if (IsBossComplete())
	{
		FinalStage();
	}
	//今のステージのボスを倒したら
	else if (isBossDefeated[currentStage])
	{
		NextStage();
	}
}

void Stage::FinalStage()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	SetStage("stage5-1");
	dh->stageNum = 5;
	currentStage = dh->stageNum;
	isBossDefeated.clear();
	isBossDefeated.resize(STAGE_MAX, false);
}

void Stage::NextStage()
{
	DataHolder* dh = FindGameObject<DataHolder>();
	//ステージが最終ステージならタイトルに
	if (currentStage == 5)
	{
		SceneManager::ChangeScene(SCENE_NAME::CLEAR_SCENE);
	}
	//それ以外のボスなら次のステージに
	else if (currentStage != 5)
	{
		isStartSection = true;
		std::string name = "stage" + std::to_string(dh->stageNum) + "-1";
		SetStage(name);
		currentStage = dh->stageNum;
		dh->stageNum += 1;
		//通常ステージの最後以上になったら1に戻す
		if (dh->stageNum > STAGE_MAX - 2)
		{
			dh->stageNum = 1;
		}
	}

	
}

void Stage::PreviousSection()
{
	direction = Direction::PREVIOUS;
	if (currentNum - 1 >= 0)
	{
		SetStage(mapName[currentNum - 1]);
	}
}

void Stage::DefeatedBoss()
{
	isBossDefeated[currentStage] = true;
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

Vector2D Stage::GetAnimationPos()
{
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			//入り口の場所をアニメーションの開始位置に
			if (map[y][x] == PREVIOUSPORTAL_CSV_NUM) {
				return Vector2D((float)(x * IMAGE_SCALE), (float)(y * IMAGE_SCALE));
				break;
			}
		}
	}
	return Vector2D(0,0);
}

Vector2D Stage::CalculateLaserEnd(Vector2D start, Vector2D dir, int length)
{
	//返す値を保存する変数
	Vector2D current = start;
	//長さ分1px毎に検索
	for (int i = 0; i < length; i++)
	{
		current = Math2D::Add(current, dir);
		//壁との判定
		int mapX = (int)current.x / IMAGE_SCALE;
		int mapY = (int)current.y / IMAGE_SCALE;
		if (IsInWall((int)current.x, (int)current.y))
		{
			//壁に少しめり込ませる
			current = Math2D::Add(current, Math2D::Mul(dir, 10));
			return current;
		}
	}

	//壁に当たらなかったら長さ分返す
	return current;

	return Vector2D();
}

void Stage::SetScroll()
{
	Stage::mapBottom = (int)(map.size() * IMAGE_SCALE - (WIN_HEIGHT / SCREEN_ZOOM));
	Stage::mapTop = 0;
	Stage::mapLeft = 0;
	Stage::mapRight = (int)(map[0].size() * IMAGE_SCALE - (WIN_WIDTH / SCREEN_ZOOM));

	Stage::scrollX = Stage::mapLeft;
	Stage::scrollY = Stage::mapBottom;
}

float Stage::GetScrollY()
{
	Player* p = FindGameObject<Player>();
	return Stage::scrollY + p->GetCameraY();
}

void Stage::SetPlayer()
{
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == PLAYER_CSV_NUM) {
				//プレイヤーの生成の際、サイズの違いにより床に埋まるので一マス上に出現させる
				new Player(x * IMAGE_SCALE, (y - 1) * IMAGE_SCALE);
				break;
			}

		}
	}
}

void Stage::SetPlayerPosition()
{
	int findNum;
	if (direction == Direction::NEXT && (isStartSection || isBossSection))
	{
		findNum = PLAYERSPAWN_CSV_NUM;
	}
	else if (direction == Direction::NEXT)
	{
		findNum = PREVIOUSPORTAL_CSV_NUM;
	}
	else if (direction == Direction::PREVIOUS)
	{
		findNum = NEXTPORTAL_CSV_NUM;
	}

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			//階段と同じ場所に
			if (map[y][x] == findNum) {
				Player* p = FindGameObject<Player>();
				//プレイヤーの生成の際、サイズの違いにより床に埋まるので一マス上に送る
				p->SetPosition({ (float)x * IMAGE_SCALE, ((float)y - 1) * IMAGE_SCALE });
				break;
			}

		}
	}
}

void Stage::SetEnemy_Boss()
{
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == KURIBOH_CSV_NUM) {
				//プレイヤーの生成の際、サイズの違いにより床に埋まるので一マス上に出現させる
				new Kuriboh(Vector2D((float)(x * IMAGE_SCALE), (float)((y - 1) * IMAGE_SCALE)));
				break;
			}
			if (map[y][x] == FAIRY_CSV_NUM) {
				new Fairy(Vector2D((float)(x * IMAGE_SCALE), (float)((y - 1) * IMAGE_SCALE)));
				break;
			}
			if (map[y][x] == TURRET_CSV_NUM) {
				new Turret(Vector2D((float)(x * IMAGE_SCALE), (float)((y - 1) * IMAGE_SCALE)));
				break;
			}
			if (map[y][x] == BOMBER_CSV_NUM) {
				new Bomber(Vector2D((float)(x * IMAGE_SCALE), (float)((y - 1) * IMAGE_SCALE)));
				break;
			}
			if (map[y][x] == BOSS01_CSV_NUM)
			{
				new Santana(Vector2D((float)(x * IMAGE_SCALE), (float)((y - 1) * IMAGE_SCALE)));
				//new Boss(Vector2D((float)(x * IMAGE_SCALE), (float)(y * IMAGE_SCALE)), BossNumber::BOSS01);
				//ボスがいるかどうかをtrueに
				isBossSection = true;
				break;
			}

		}
	}
}

void Stage::DeleteObjects()
{
	auto gmmick = FindGameObjects<Gimmick>();
	for (auto gm : gmmick)
	{
		gm->DestroyMe();
	}
	auto enemy = FindGameObjects<Enemy>();
	for (auto e : enemy) {
		e->DestroyMe();
	}
	Boss* boss = FindGameObject<Boss>();
	if (boss != nullptr) {
		boss->DestroyMe();
	}
}
