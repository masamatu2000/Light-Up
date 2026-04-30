#include "SoundManager.h"
#include"CsvReader.h"
/// <summary>
/// なぜかファウンドゲームオブジェクトがうまく使えないため使うためにいちいちnewしている
/// </summary>

Sound::Sound()
{
	SetEeFile();

	SetBgmFile();

	SetSeVolume(50);
	SetBgmVolume(50);

	isBgmPlay = false;
}

Sound::~Sound()
{
}

/// <summary>
/// サウンドの再生を行う
/// Imnameは、ファイルの名前。
/// </summary>
/// <param name="Imname"></param>
/// <param name="playtype"></param>
void Sound::EffectSoundPlay(std::string Imname)
{
	int size = esName.size();
	for (int y = 0; y < size; y++) {
		if (Imname == esName[y]) {
			PlaySoundMem(esFileName[y], DX_PLAYTYPE_BACK);
		}
	}
}

/// <summary>
/// BGMの再生を行う
/// Imnameは、ファイルの名前。
/// </summary>
/// <param name="Imname"></param>
void Sound::BgmPlay(std::string Imname)
{
	if (isBgmPlay)
	{
		return;
	}
	else
	{
		isBgmPlay = true;
	}
	int size = bgmName.size();
	for (int y = 0; y < size; y++) {
		if (Imname == bgmName[y]) {
			PlaySoundMem(bgmFileName[y], DX_PLAYTYPE_LOOP);
		}
	}
}

/// <summary>
/// すべてのサウンドの再生を停止する
/// </summary>
void Sound::SoundStop()
{
	for (int i = 0; i < bgmName.size(); i++)
	{
		if (CheckSoundMem(bgmFileName[i]))
		{
			StopSoundMem(bgmFileName[i]);
		}
	}
	for (int i = 0; i < esName.size(); i++)
	{
		if (CheckSoundMem(esFileName[i]))
		{
			StopSoundMem(esFileName[i]);
		}
	}
	isBgmPlay = false;
}

/// <summary>
/// BGMのボリュームを設定する
/// volumeは、0～255の整数値で指定する
/// </summary>
/// <param name="volume"></param>
void Sound::SetBgmVolume(int volume)
{
	for (int i = 0; i < bgmName.size(); i++)
	{
		ChangeVolumeSoundMem(volume, bgmFileName[i]);
	}
}

/// <summary>
/// サウンドのボリュームを設定する
/// volumeは、0～255の整数値で指定する
/// </summary>
/// <param name="volume"></param>
void Sound::SetSeVolume(int volume)
{
	for (int i = 0; i < esName.size(); i++)
	{
		ChangeVolumeSoundMem(volume, esFileName[i]);
	}
}

void Sound::SetEeFile()
{
	CsvReader* csv = new CsvReader("data/sound/ES/SeName.csv");
	int lines = csv->GetLines();//行数を取得
	esFileName.clear();
	esFileName.resize(lines);//mapの行数を設定
	esName.clear();
	esName.resize(lines);
	for (int y = 0; y < lines; y++) {//1行ずつ読む
		//改行を消すため一時保存
		std::string str = csv->GetString(y, 0);

		//改行がある場合
		if (!str.empty() && str.back() == '\r' || !str.empty() && str.back() == '\n')
		{
			str.pop_back();
		}

		esName[y] = str;

		std::string path = "data/sound/ES/" + esName[y] + ".mp3";
		esFileName[y] = LoadSoundMem(path.c_str());
	}
	delete csv;
}

void Sound::SetBgmFile()
{
	CsvReader* csv = new CsvReader("data/sound/BGM/BgmName.csv");
	int lines = csv->GetLines();//行数を取得
	bgmFileName.clear();
	bgmFileName.resize(lines);//mapの行数を設定
	bgmName.clear();
	bgmName.resize(lines);
	for (int y = 0; y < lines; y++) {//1行ずつ読む
		//改行を消すため一時保存
		std::string str = csv->GetString(y, 0);

		//改行がある場合
		if (!str.empty() && str.back() == '\r' || !str.empty() && str.back() == '\n')
		{
			str.pop_back();
		}

		bgmName[y] = str;

		std::string path =  "data/sound/BGM/" + bgmName[y] + ".wav";
		bgmFileName[y] = LoadSoundMem(path.c_str());
	}
	delete csv;
}
