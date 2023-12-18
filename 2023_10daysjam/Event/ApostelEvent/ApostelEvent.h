#pragma once
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
	const std::list<Apostel_ThrowMine*>& GetThrowMine() { return apostel_->GetThrowMine(); }

	/// <summary>
	/// ゲージ用にHpだけ受け取る奴
	/// </summary>
	/// <returns></returns>
	int GetDicHp() { return getHp_; };
	//void SetDicHp(int dichp) { getHp_ = dichp; };

private:
	Apostel* apostel_ = nullptr;
	int getHp_;
};

