#include "ApostelEvent.h"

ApostelEvent::~ApostelEvent()
{
	delete apostel_;
}

void ApostelEvent::Initialize()
{
	apostel_ = new Apostel;
	apostel_->Initialize({500,100},{0,0},10.f);
}

void ApostelEvent::Update()
{
	apostel_->Update();
	//ゲージ用
	getHp_ = int(apostel_->GetDecreasedHp());
}

void ApostelEvent::Draw()
{
	apostel_->Draw();
}

void ApostelEvent::SetPlayerInfo(CharaBase player)
{
	apostel_->SetPlayerBase(player);
}
