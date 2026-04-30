#pragma once
#include "GameObject.h"
#include<vector>
#include<string.h>
/// <summary>
/// 
/// </summary>

//Stageでnewしてるよ

class Sound : GameObject
{
public:
	Sound();
	~Sound();
	void EffectSoundPlay(std::string Imname);
	void BgmPlay(std::string Imname);
	void SoundStop();
	void SetBgmVolume(int volume);
	void SetSeVolume(int volume);

private:
	std::vector<std::string> esName;
	std::vector<int> esFileName;

	std::vector<std::string> bgmName;
	std::vector<int> bgmFileName;

	bool isBgmPlay;
private:
	void SetEeFile();
	void SetBgmFile();
};