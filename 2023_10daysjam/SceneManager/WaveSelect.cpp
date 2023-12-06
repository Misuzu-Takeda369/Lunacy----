#include "WaveSelect.h"

WaveSelect::WaveSelect()
{
}

WaveSelect::~WaveSelect()
{
}

void WaveSelect::Initialize()
{
	mousePos_ = { 0,0 };

	changeTimingFrame_ = 0;

	nowWave_ = Tutorial;

	maxWave_ = Tutorial;
}

void WaveSelect::Initialize(int& maxWave)
{
	mousePos_ = { 0,0 };

	changeTimingFrame_ = 0;

	nowWave_ = Tutorial;
	maxWave_ = maxWave;

	selectLetter_[0] = {
		100,50 + (textSize_.y_ * 4)
	};
	selectLetter_[1] = {
		450,50 + (textSize_.y_*0)
	};
	selectLetter_[2] = {
		450,50 + (textSize_.y_ * 2)
	};
	selectLetter_[3] = {
		450,50 + (textSize_.y_ * 4)
	};
	
	image_[0] = Novice::LoadTexture("./Resources/images/Text/tutrial.png");
	image_[1] = Novice::LoadTexture("./Resources/images/Text/wave1.png");
	image_[2] = Novice::LoadTexture("./Resources/images/Text/wave2.png");
	image_[3] = Novice::LoadTexture("./Resources/images/Text/wave3.png");
	
	backImage_ = Novice::LoadTexture("./Resources/images/Back/Titleback_1.png");

	ColorLode();
}

void WaveSelect::Update()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	changeTimingFrame_++;

	MouseBottonChack();

#ifdef _DEBUG

	//現在は1を押したときに移動
	if ((preKeys[DIK_I] == 0 && keys[DIK_I] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
		flagChange_ = true;
		changeTimingFrame_ = 0;
	}

#endif // _DEBUG

}

void WaveSelect::Draw()
{
	//背景
	Novice::DrawSprite(0,0, backImage_,1, 1, 0.0f, 0x93829CFF);



	for (int i = 0; i < selectNum_; i++) {

		Novice::DrawSprite(selectLetter_[i].x_, selectLetter_[i].y_, image_[i],1,1, 0.0f,selectColor_[i].color);
	}

}

void WaveSelect::MouseBottonChack()
{
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);

#pragma region Tutrial

	if (maxWave_ >= Tutorial) {
		if ((mousePos_.x_ >= selectLetter_[0].x_ && mousePos_.x_ <= selectLetter_[0].x_ + tutrialSize_.x_)
			&&
			(mousePos_.y_ >= selectLetter_[0].y_ && mousePos_.y_ <= selectLetter_[0].y_ + tutrialSize_.y_))
		{

			selectColor_[0].color = RED;
			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Tutorial;
				changeTimingFrame_ = 0;
			}


		}
		else {
			selectColor_[0].color = WHITE;
		}
	}

#pragma endregion

#pragma region Wave1
	if (maxWave_ >= Wave1) {
		if ((mousePos_.x_ >= selectLetter_[1].x_ && mousePos_.x_ <= selectLetter_[1].x_ + textSize_.x_)
			&&
			(mousePos_.y_ >= selectLetter_[1].y_ && mousePos_.y_ <= selectLetter_[1].y_ + textSize_.y_))
		{
			selectColor_[1].color = RED;
			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Wave1;
				changeTimingFrame_ = 0;
			}

		}
		else {
			selectColor_[1].color = WHITE;
		}

	}
#pragma endregion

#pragma region Wave2

	if (maxWave_ >= Wave2) {

		if ((mousePos_.x_ >= selectLetter_[2].x_ && mousePos_.x_ <= selectLetter_[2].x_ + textSize_.x_)
			&&
			(mousePos_.y_ >= selectLetter_[2].y_ && mousePos_.y_ <= selectLetter_[2].y_ + textSize_.y_))
		{
			selectColor_[2].color = RED;
			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Wave2;
				changeTimingFrame_ = 0;
			}

		}
		else {
			selectColor_[2].color = WHITE;
		}
	}

#pragma endregion

#pragma region Wave3

	if (maxWave_ >= Wave3) {
		if ((mousePos_.x_ >= selectLetter_[3].x_ && mousePos_.x_ <= selectLetter_[3].x_ + textSize_.x_)
			&&
			(mousePos_.y_ >= selectLetter_[3].y_ && mousePos_.y_ <= selectLetter_[3].y_ + textSize_.y_))
		{
			selectColor_[3].color = RED;
			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Wave3;
				changeTimingFrame_ = 0;
			}


		}
		else {
			selectColor_[3].color = WHITE;
		}
	}

#pragma endregion
}

void WaveSelect::ColorLode()
{
	for (int i = 0; i < selectNum_; i++) {
		selectColor_[i].color = BLACK;
	}

	if (maxWave_ >=0) {
		selectColor_[0].color = WHITE;
	}
	if (maxWave_ >= 1) {
		selectColor_[1].color = WHITE;
	}
	if (maxWave_ >= 2) {
		selectColor_[2].color = WHITE;
	}
	if (maxWave_ >= 3) {
		selectColor_[3].color = WHITE;
	}

}
