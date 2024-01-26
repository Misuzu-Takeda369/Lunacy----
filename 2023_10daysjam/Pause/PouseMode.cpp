#include "PouseMode.h"


void PouseMode::Initialize()
{
	
	imageGMPauseText_ = Novice::LoadTexture("./Resources/images/Text/PauseText.png");
	imagePlayBackText_ = Novice::LoadTexture("./Resources/images/Text/PTGameBack.png");
	imageTitleBackText_ = Novice::LoadTexture("./Resources/images/Text/PTTitleBack.png");
	textFrameImage_ = Novice::LoadTexture("./Resources/images/Back/Textfream.png");
	yesImage_ = Novice::LoadTexture("./Resources/images/Text/ChackYES.png");
	noImage_ = Novice::LoadTexture("./Resources/images/Text/ChackNO.png");
	chacktextImage_ = Novice::LoadTexture("./Resources/images/Text/ChackQ.png");

	selectEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_system26.wav");
	decisionEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_system13.wav");

	OnselectPousePlay_ = false;
	OnSelectPTextPlay_[0] = false;
	OnSelectPTextPlay_[1] = false;

	OnSelectPChackPlay_[0] = false;
	OnSelectPChackPlay_[1] = false;

	selectEffectPlay_ = 0;
	//decisionEffecttPlay_ = 0;


	GMPauseTextPos_ = { 1100,10 };

	PMPauseTextPos_[0] = {500,20};
	PMPauseTextPos_[1] = { 100,200 };
	PMPauseTextPos_[2] = { 100,500 };

	chackTextPos_[0] = { 330, 200 };
	chackTextPos_[1] = { 330, 200 };


}

void PouseMode::Update(int gameSModeNow)
{

	gameSModeNow_ = gameSModeNow;

	switch (gameSModeNow_)
	{
	case 0:

		if ((mousePos_.x_ >= GMPauseTextPos_.x_ && mousePos_.x_ <= GMPauseTextPos_.x_ + size_.x_)
			&&
			(mousePos_.y_ >= GMPauseTextPos_.y_ && mousePos_.y_ <= GMPauseTextPos_.y_ + size_.y_))
		{

			notAttackFrag_ = true;

			imageColor_.color = YELLOW;
			//連続でならないようにするやつ
			if (OnselectPousePlay_ == false) {

				OnselectPousePlay_ = true;

				//マウスに触れたときに音が鳴る
				if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
					Novice::PlayAudio(selectEffect_, 0, 1);
				}
			}

			if (Novice::IsTriggerMouse(0)) {
				changeFrag_ = true;

				Novice::StopAudio(selectEffect_);
				Novice::PlayAudio(decisionEffect_, 0, 2);
			}

		}
		else {
			imageColor_.color = WHITE;
			OnselectPousePlay_ = false;
			notAttackFrag_ = false;
		}
		break;

	case 1:

		if (!chackFrage_) {

			//ゲームを続けるかタイトルに戻るかを選択する
			if ((mousePos_.x_ >= PMPauseTextPos_[1].x_ && mousePos_.x_ <= PMPauseTextPos_[1].x_ + size_.x_ + 128)
				&&
				(mousePos_.y_ >= PMPauseTextPos_[1].y_ && mousePos_.y_ <= PMPauseTextPos_[1].y_ + size_.y_))
			{

				PimageColor_[0].color = RED;
				//連続でならないようにするやつ
				if (OnSelectPTextPlay_[0] == false) {

					OnSelectPTextPlay_[0] = true;

					//マウスに触れたときに音が鳴る
					if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
						Novice::PlayAudio(selectEffect_, 0, 1);
					}
				}

				if (Novice::IsTriggerMouse(0)) {
					changeFrag_ = true;

					Novice::StopAudio(selectEffect_);
					Novice::PlayAudio(decisionEffect_, 0, 2);

				}

			}
			else {
				PimageColor_[0].color = WHITE;
				OnSelectPTextPlay_[0] = false;
			}


			if ((mousePos_.x_ >= PMPauseTextPos_[2].x_ && mousePos_.x_ <= PMPauseTextPos_[2].x_ + size_.x_ + 128)
				&&
				(mousePos_.y_ >= PMPauseTextPos_[2].y_ && mousePos_.y_ <= PMPauseTextPos_[2].y_ + size_.y_))
			{

				PimageColor_[1].color = RED;
				//連続でならないようにするやつ
				if (OnSelectPTextPlay_[1] == false) {

					OnSelectPTextPlay_[1] = true;

					//マウスに触れたときに音が鳴る
					if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
						Novice::PlayAudio(selectEffect_, 0, 1);
					}
				}

				if (Novice::IsTriggerMouse(0)) {
					chackFrage_ = true;
					Novice::StopAudio(selectEffect_);
					Novice::PlayAudio(decisionEffect_, 0, 2);
				}

			}
			else {
				PimageColor_[1].color = WHITE;
				OnSelectPTextPlay_[1] = false;
			}
		}
		else {
			//YESかNOか
			ChackUpdate();
		}
		

		break;


	default:
		break;
	}

	//そこ押したら変わるよーっていうやつ
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);
}

void PouseMode::Draw(int gameSModeNow, Vector2 ShakePos)
{
	gameSModeNow_ = gameSModeNow;

	switch (gameSModeNow_)
	{

	case 0:
		//ゲームモード
		Novice::DrawSprite(GMPauseTextPos_.x_ + int(ShakePos.x), GMPauseTextPos_.y_ + int(ShakePos.y), imageGMPauseText_, 0.5, 0.5, 0.0f, imageColor_.color);

		break;

	case 1:
		//ポーズ
		Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f, 0x4A3180B3, kFillModeSolid);

		

			Novice::DrawSprite(PMPauseTextPos_[0].x_, PMPauseTextPos_[0].y_, imageGMPauseText_, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(PMPauseTextPos_[1].x_, PMPauseTextPos_[1].y_, imagePlayBackText_, 1, 1, 0.0f, PimageColor_[0].color);
			Novice::DrawSprite(PMPauseTextPos_[2].x_, PMPauseTextPos_[2].y_, imageTitleBackText_, 1, 1, 0.0f, PimageColor_[1].color);
		

			if (chackFrage_) {
				ChackDraw();
			}
			
		

		break;

	default:
		break;
	}

}

void PouseMode::ChackUpdate()
{
	if ((mousePos_.x_ >= chackTextPos_[0].x_ && mousePos_.x_ <= chackTextPos_[0].x_ + size_.x_)
		&&
		(mousePos_.y_ >= chackTextPos_[0].y_+100 && mousePos_.y_ <= chackTextPos_[0].y_ + 100 + size_.y_))
	{

		chackColor_[0].color = RED;

		//連続でならないようにするやつ
		if (OnSelectPChackPlay_[0] == false) {

			OnSelectPChackPlay_[0] = true;

			//マウスに触れたときに音が鳴る
			if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
				Novice::PlayAudio(selectEffect_, 0, 1);
			}
		}

		if (Novice::IsTriggerMouse(0)) {
			changeFrag_ = false;
			titleChangeFrag_ = true;
			chackFrage_ = false;

			Novice::StopAudio(selectEffect_);
			Novice::PlayAudio(decisionEffect_, 0, 2);

		}

	}
	else {
		chackColor_[0].color = WHITE;
		OnSelectPChackPlay_[0] = false;
	}

	if ((mousePos_.x_ >= chackTextPos_[1].x_ +350 && mousePos_.x_ <= chackTextPos_[1].x_+350 + size_.x_)
		&&
		(mousePos_.y_ >= chackTextPos_[1].y_ + 100 && mousePos_.y_ <= chackTextPos_[1].y_ + 100 + size_.y_))
	{

		chackColor_[1].color = RED;

		//連続でならないようにするやつ
		if (OnSelectPChackPlay_[1] == false) {

			OnSelectPChackPlay_[1] = true;

			//マウスに触れたときに音が鳴る
			if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
				Novice::PlayAudio(selectEffect_, 0, 1);
			}
		}

		if (Novice::IsTriggerMouse(0)) {
			chackFrage_ = false;
			Novice::StopAudio(selectEffect_);
			Novice::PlayAudio(decisionEffect_, 0, 2);
		}

	}
	else {
		chackColor_[1].color = WHITE;
		OnSelectPChackPlay_[1] = false;
	}
}

void PouseMode::ChackDraw()
{
	Novice::DrawSprite(330, 200, textFrameImage_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(330, 200, chacktextImage_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(chackTextPos_[0].x_, chackTextPos_[0].y_, yesImage_, 1, 1, 0.0f, chackColor_[0].color);
	Novice::DrawSprite(chackTextPos_[1].x_, chackTextPos_[1].y_, noImage_, 1, 1, 0.0f, chackColor_[1].color);

}
