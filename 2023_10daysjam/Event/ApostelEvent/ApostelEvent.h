#pragma once
#include "Apostel.h"
#include "CharaBase.h"
//#include "LunaticAngel.h"
class ApostelEvent
{
public:
	~ApostelEvent();
	void Initialize();
	void Update();
	void Draw();
	void SetPlayerInfo(CharaBase player);
	bool GetIsDead() { return apostel_->GetIsDead(); }
	Object* GetObjectInfo() { return (Object*)apostel_; }
	void OnCollision(float& dmg) { apostel_->OnCollision(dmg); }
	const std::list<Apostel_MagicBall*>& GetMagicBall() { return apostel_->GetMagicBall(); }
	const std::list<Apostel_ThrowMine*>& GetThrowMine() { return apostel_->GetThrowMine(); }

	/// <summary>
	/// ゲージ用にHpだけ受け取る奴
	/// </summary>
	/// <returns></returns>
	int GetDicHp() { return getHp_; };

private:
	Apostel* apostel_ = nullptr;
	//LunaticAngel* angel_ = nullptr;
	bool isApostelActive_ = false;
	int time_;
	float warpScale_ = 0;
	Vector2 warpPos_;
	//int warpFrame_ = 0;
	bool isWarped_ = false;
	unsigned int warpGateImage_;
	float gateTheta_ = 0;
	UnitColor gateColor_;

	int getHp_;
};

