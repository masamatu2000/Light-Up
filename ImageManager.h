#pragma once
#include "GameObject.h"
#include<vector>
#include<string.h>
class Image : GameObject
{
public:
	Image();
	~Image();
	int ReturnImage(std::string Imname);
private:
	std::vector<std::vector<int>> Images;
};