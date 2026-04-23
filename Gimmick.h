#pragma once
#include"Object.h"
/// <summary>
/// ギミック（死体や罠）の管理をするクラス
/// </summary>
/// <author>H.suginunma</author>

//ギミックの種類
enum class GimmickType
{
	CORPSE
};

class Gimmick : public Object
{
public:
	Gimmick();
	~Gimmick();
	GimmickType GetGimmickType() { return gimmicType; }
protected:
	void Update() override;
	void Draw() override;
	//壁との判定
	float CheckHitWall(std::string wall);
	GimmickType gimmicType;
};