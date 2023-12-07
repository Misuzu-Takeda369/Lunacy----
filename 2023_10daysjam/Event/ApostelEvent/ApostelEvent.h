﻿#pragma once
#include "Apostel.h"
#include "CharaBase.h"
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

	///判定用
	float GetHp() {return hp_;}

private:
	Apostel* apostel_ = nullptr;

	float hp_;
};
