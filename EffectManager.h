#pragma once
#include "Object.h"

class Effect : Object
{
public:
	Effect();
	Effect(int x, int y);
	~Effect();

	void Update()override;
	void Draw()override;
private:
	int patX;//c‚É‰½ŒÂ–ÚH
	int patY;//‰¡‚É‰½ŒÂ–ÚH
	int patCounter;
};