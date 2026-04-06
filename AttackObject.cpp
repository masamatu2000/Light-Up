#include "AttackObject.h"

AttackObject::AttackObject()
{
}

AttackObject::~AttackObject()
{
}

void AttackObject::Update()
{
}

void AttackObject::Draw()
{
}

void AttackObject::Attack()
{
}

void AttackObject::CheckDirection()
{
	//Œü‚«‚ğ¶‚É
	if (islookleft)
	{
		dir = { -1,0 };
	}
	//Œü‚«‚ğ‰E‚É
	else if (!islookleft)
	{
		dir = { 1,0 };
	}
}