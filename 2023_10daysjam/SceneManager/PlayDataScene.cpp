#include "PlayDataScene.h"
#include <Novice.h>

void PlayDataScene::Initialize()
{
	backTitleButton_ = Novice::LoadTexture("./Resources/images/UI/backbutton.png");
	datawall1_ = Novice::LoadTexture("./Resources/images/Back/datawall1.png");
	commentBack_ = Novice::LoadTexture("./Resources/images/Back/sleep.png");
	dataText1_= Novice::LoadTexture("./Resources/images/Text/dataText1.png");
	koron_ = Novice::LoadTexture("./Resources/images/number/koron.png");
}

void PlayDataScene::Update()
{
	MouseBottonChack();
	//時間
	time_[0] = int(data_->GetPlayHour()/10);
	timeNum_ = data_->GetPlayHour() % 10;
	time_[1] = timeNum_;
	//分
	time_[2] = int(data_->GetPlayMin() / 10);
	timeNum_ = data_->GetPlayMin() % 10;
	time_[3] = timeNum_;
	//秒
	time_[4] = int(data_->GetPlaySecond() / 10);
	timeNum_ = data_->GetPlaySecond() % 10;
	time_[5] = timeNum_;
}

void PlayDataScene::SetSaveData(SaveData* data)
{
	data_ = data;
}

void PlayDataScene::Draw()
{
	//今のプレイ時間を表示
	//Novice::ScreenPrintf(500, 500, "time %02d:%02d:%02d", data_->GetPlayHour(), data_->GetPlayMin(), data_->GetPlaySecond());
	Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
	Novice::DrawSprite(0, 0, datawall1_, 1, 1, 0, WHITE);
	Novice::DrawSprite(0, 0, dataText1_, 1, 1, 0, WHITE);
	Novice::DrawSprite(512, 0, commentBack_, 1, 1, 0, WHITE);
	Novice::DrawSprite(512, 0, tips_[tipsNum_], 1, 1, 0, WHITE);
	Novice::DrawSprite(backButtonPos_.x_, backButtonPos_.y_, backTitleButton_, 0.25f, 0.25f, 0, WHITE);
	Novice::DrawSprite(200, 160, numSprite[data_->GetLastWave()], 0.75f, 0.75f, 0, WHITE);
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite(i * 60 + 50, 400, numSprite[time_[i]], 0.75f, 0.75f, 0, WHITE);
	}
	for (int i = 2; i < 4; i++) {
		Novice::DrawSprite(i * 60 + 50+30, 400, numSprite[time_[i]], 0.75f, 0.75f, 0, WHITE);
	}
	for (int i = 4; i < 6; i++) {
		Novice::DrawSprite(i * 60 + 50+60, 400, numSprite[time_[i]], 0.75f, 0.75f, 0, WHITE);
	}
	Novice::DrawSprite(2 * 60 + 40, 400, koron_, 0.75f, 0.75f, 0, WHITE);
	Novice::DrawSprite(4 * 60 + 60, 400, koron_, 0.75f, 0.75f, 0, WHITE);
}

void PlayDataScene::MouseBottonChack()
{
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);

	if ((mousePos_.x_ >= backButtonPos_.x_ && mousePos_.x_ <= backButtonPos_.x_ + buttonSize_)
		&&
		(mousePos_.y_ >= backButtonPos_.y_&& mousePos_.y_ <= backButtonPos_.y_ + buttonSize_)) {

		if (Novice::IsTriggerMouse(0)) {
			backTitleFlag = true;
		}
	}
}
