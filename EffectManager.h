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

	void CheckDirection();

private:
	int patX;//c‚É‰½ŒÂ–ÚH
	int patY;//‰¡‚É‰½ŒÂ–ÚH
	int patCounter;
	

};

enum EffectName
{
	LiteUp_,
	LiteUp_Bullet_,
	New_Piskel
};