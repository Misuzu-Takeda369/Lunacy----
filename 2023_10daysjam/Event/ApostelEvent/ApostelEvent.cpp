#include "ApostelEvent.h"
#include "Function/Function.h"

ApostelEvent::~ApostelEvent()
{
	delete apostel_;
	//delete angel_;
}

void ApostelEvent::Initialize()
{
	apostel_ = new Apostel;
	apostel_->Initialize({500,100},{0,0},10.f);
	//angel_ = new LunaticAngel;
	//angel_->Initialize({ 0,0 }, { 0,0 }, 0);
	time_ = 0;
	warpPos_ = { 1200.f,300.f };
	warpScale_ = 0;
	//radiusSpeed_ = 2;
	//warpFrame_ = 7;
	isWarped_ = false;
	warpGateImage_ = Novice::LoadTexture("./Resources/Images/WarpGate.png");
	gateColor_.R = 255; gateColor_.G = 255; gateColor_.B = 255; gateColor_.A = 0;


}

void ApostelEvent::Update()
{
	if (!isApostelActive_) {
		//ここに登場シーンを 1秒用
		time_++;
		
		gateTheta_ += 0.18f;
		if (time_<=30) {
			
			if (warpScale_ < 2.f) {
				warpScale_ += 0.1f;
			}
			
		}
		if (gateColor_.A < 255) {
			gateColor_.A += 10;
			if (gateColor_.A > 255) {
				gateColor_.A = 255;
			}
		}

		if (time_ >= 30) {
			
			isWarped_ = true;
			
		}
		if (time_ >= 40) {
			if (warpScale_ > 0) {
				warpScale_ -= 0.1f;
				gateColor_.A -= 10;
				if (gateColor_.A < 0) {
					gateColor_.A = 0;
				}
			}
		}
		/*
		if (warpRadius_ >= 60) {
			radiusSpeed_ = -radiusSpeed_;
			isWarped_ = true;
		}*/
		if (time_>=60) {
			isApostelActive_ = true;
		}
		gateColor_.color=GetColorValue(gateColor_.R, gateColor_.G, gateColor_.B, gateColor_.A);
	}
	else {
		if (warpScale_ > 0) {
			warpScale_ -= 0.1f;
		}
		apostel_->Update();
	}
	if (apostel_->GetIsDead()) {
		//angel_->Update();
	}
}

void ApostelEvent::Draw()
{
	//angel_->Draw();
	if (isWarped_) {
	apostel_->Draw();
	}
	//Novice::DrawEllipse((int)warpPos_.x, (int)warpPos_.y, warpRadius_, warpRadius_, 0, BLACK, kFillModeSolid);
	//DrawRotateSprite(warpPos_, { 64.f,64.f }, 64*warpFrame_, 0, warpGateImage_, gateColor_.color, gateTheta_);
	DrawRotateScaleSprite(warpPos_, { 64.f,64.f }, 0, 0, warpGateImage_, gateColor_.color, warpScale_, gateTheta_);
}

void ApostelEvent::SetPlayerInfo(CharaBase player)
{
	apostel_->SetPlayerBase(player);

}
