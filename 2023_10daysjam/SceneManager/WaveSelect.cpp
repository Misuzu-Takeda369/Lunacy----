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

	titleChangeFlag_ = false;
}

void WaveSelect::Initialize(int& maxWave)
{
	mousePos_ = { 0,0 };

	changeTimingFrame_ = 0;

	nowWave_ = Tutorial;
	maxWave_ = maxWave;

	titleChangeFlag_ = false;

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

	selectLetter_[4] = {
		1020,50 + (textSize_.y_ * 4)
	};


	image_[0] = Novice::LoadTexture("./Resources/images/Text/tutrial.png");
	image_[1] = Novice::LoadTexture("./Resources/images/Text/wave1.png");
	image_[2] = Novice::LoadTexture("./Resources/images/Text/wave2.png");
	image_[3] = Novice::LoadTexture("./Resources/images/Text/wave3.png");
	image_[4] = Novice::LoadTexture("./Resources/images/Text/Boss.png");
	
	backImage_ = Novice::LoadTexture("./Resources/images/Back/Titleback_1.png");
	backTitleImage_ = Novice::LoadTexture("./Resources/images/UI/backbutton.png");

	ColorLode();

	///音関連(リソース) 
	selectEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_system26.wav");
	decisionEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_system13.wav");
	//音の尺が短すぎて機能してない(意味ない)かも
	selectEffectPlay_ = 0;
	//画像を少しデカくしたらおもろそう
	ScaleSizeX = 0.25f;
	ScaleSizeY = 0.25f;
	
}

void WaveSelect::Update()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	changeTimingFrame_++;

	//ステージへ移動
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

	//バックの奴
	Novice::DrawSprite(selectLetter_[0].x_, 10, backTitleImage_, ScaleSizeX, ScaleSizeY, 0.0f, WHITE);
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
			//連続でならないようにするやつ
			if (OnselectWavePlay_[0] == false) {

				OnselectWavePlay_[0] = true;

				//マウスに触れたときに音が鳴る
				if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
					Novice::PlayAudio(selectEffect_, 0, 1);
				}
			}

			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Tutorial;
				changeTimingFrame_ = 0;
				Novice::StopAudio(selectEffect_);
				Novice::PlayAudio(decisionEffect_, 0, 2);
			}


		}
		else {
			selectColor_[0].color = WHITE;
			OnselectWavePlay_[0] = false;
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
			//連続でならないようにするやつ
			if (OnselectWavePlay_[1] == false) {

				OnselectWavePlay_[1] = true;

				//マウスに触れたときに音が鳴る
				if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
					Novice::PlayAudio(selectEffect_, 0, 1);
				}
			}

			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Wave1;
				changeTimingFrame_ = 0;
				Novice::StopAudio(selectEffect_);
				Novice::PlayAudio(decisionEffect_, 0, 2);
			}

		}
		else {
			selectColor_[1].color = WHITE;
			OnselectWavePlay_[1] = false;
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

			//連続でならないようにするやつ
			if (OnselectWavePlay_[2] == false) {

				OnselectWavePlay_[2] = true;

				//マウスに触れたときに音が鳴る
				if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
					Novice::PlayAudio(selectEffect_, 0, 1);
				}
			}

			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Wave2;
				changeTimingFrame_ = 0;
				Novice::StopAudio(selectEffect_);
				Novice::PlayAudio(decisionEffect_, 0, 2);
			}

		}
		else {
			selectColor_[2].color = WHITE;
			OnselectWavePlay_[2] = false; 
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

			//連続でならないようにするやつ
			if (OnselectWavePlay_[3] == false) {

				OnselectWavePlay_[3] = true;

				//マウスに触れたときに音が鳴る
				if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
					Novice::PlayAudio(selectEffect_, 0, 1);
				}
			}

			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Wave3;
				changeTimingFrame_ = 0;
				Novice::StopAudio(selectEffect_);
				Novice::PlayAudio(decisionEffect_, 0, 2);
			}


		}
		else {
			selectColor_[3].color = WHITE;
			OnselectWavePlay_[3] = false;
		}
	}

#pragma endregion

#pragma region Boss

	if (maxWave_ >= Boss) {
		if ((mousePos_.x_ >= selectLetter_[4].x_ && mousePos_.x_ <= selectLetter_[4].x_ + textSize_.x_)
			&&
			(mousePos_.y_ >= selectLetter_[4].y_ && mousePos_.y_ <= selectLetter_[4].y_ + textSize_.y_))
		{
			selectColor_[4].color = RED;

			//連続でならないようにするやつ
			if (OnselectWavePlay_[4] == false) {

				OnselectWavePlay_[4] = true;

				//マウスに触れたときに音が鳴る
				if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
					Novice::PlayAudio(selectEffect_, 0, 1);
				}
			}

			//はじめるに入っている場合左クリックするとスターとする
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				nowWave_ = Boss;
				changeTimingFrame_ = 0;
				Novice::StopAudio(selectEffect_);
				Novice::PlayAudio(decisionEffect_, 0, 2);
			}


		}
		else {
			selectColor_[4].color = WHITE;
			OnselectWavePlay_[4] = false;
		}
	}

#pragma endregion

#pragma region BackTitle

		if ((mousePos_.x_ >= selectLetter_[0].x_ && mousePos_.x_ <= selectLetter_[0].x_ + tutrialSize_.x_)
			&&
			(mousePos_.y_ >= 10 && mousePos_.y_ <= 10 + tutrialSize_.y_))
		{
			//連続でならないようにするやつ
			if (OnselectBackPlay_ == false) {

				OnselectBackPlay_ = true;

				//マウスに触れたときに音が鳴る
				if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
					Novice::PlayAudio(selectEffect_, 0, 1);
				}
			}

			ScaleSizeX = 0.30f; ScaleSizeY = 0.30f;

		
			if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				titleChangeFlag_ = true;
				changeTimingFrame_ = 0;
				Novice::StopAudio(selectEffect_);
				Novice::PlayAudio(decisionEffect_, 0, 2);
				ScaleSizeX = 0.25f; ScaleSizeY = 0.25f;
			}


		}
		else {
			OnselectBackPlay_ = false;
			ScaleSizeX = 0.25f; ScaleSizeY = 0.25f;
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
	if (maxWave_ >= 4) {
		selectColor_[4].color = WHITE;
	}

}
