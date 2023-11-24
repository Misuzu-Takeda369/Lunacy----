#include "PlayDataScene.h"
#include <Novice.h>

void PlayDataScene::Initialize()
{
	backTitleButton_ = Novice::LoadTexture("./Resources/images/UI/backbutton.png");
}

void PlayDataScene::Update()
{
	MouseBottonChack();
}

void PlayDataScene::SetSaveData(SaveData* data)
{
	data_ = data;
}

void PlayDataScene::Draw()
{
	//今のプレイ時間を表示
	Novice::ScreenPrintf(500, 500, "time %02d:%02d:%02d", data_->GetPlayHour(), data_->GetPlayMin(), data_->GetPlaySecond());
	Novice::DrawSprite(backButtonPos_.x_, backButtonPos_.y_, backTitleButton_, 0.25f, 0.25f, 0, WHITE);
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
