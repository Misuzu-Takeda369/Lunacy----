#include "PouseMode.h"


void PouseMode::Initialize()
{
	
	imageGMPauseText_ = Novice::LoadTexture("./Resources/images/Text/PauseText.png");
	imagePlayBackText_ = Novice::LoadTexture("./Resources/images/Text/PTGameBack.png");
	imageTitleBackText_ = Novice::LoadTexture("./Resources/images/Text/PTTitleBack.png");
	textFrameImage_ = Novice::LoadTexture("./Resources/images/Back/Textfream.png");
	yesImage_ = Novice::LoadTexture("./Resources/images/Text/ChackNO.png");
	noImage_ = Novice::LoadTexture("./Resources/images/Text/ChackYES.png");


	GMPauseTextPos_ = { 1100,10 };

	PMPauseTextPos_[0] = {500,20};
	PMPauseTextPos_[1] = { 100,200 };
	PMPauseTextPos_[2] = { 100,500 };

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

			imageColor_.color = YELLOW;

			if (Novice::IsTriggerMouse(0)) {
				changeFrag_ = true;
			}

		}
		else {
			imageColor_.color = WHITE;
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

				if (Novice::IsTriggerMouse(0)) {
					changeFrag_ = true;
				}

			}
			else {
				PimageColor_[0].color = WHITE;
			}


			if ((mousePos_.x_ >= PMPauseTextPos_[2].x_ && mousePos_.x_ <= PMPauseTextPos_[2].x_ + size_.x_ + 128)
				&&
				(mousePos_.y_ >= PMPauseTextPos_[2].y_ && mousePos_.y_ <= PMPauseTextPos_[2].y_ + size_.y_))
			{

				PimageColor_[1].color = RED;

				if (Novice::IsTriggerMouse(0)) {
					chackFrage_ = true;
				}

			}
			else {
				PimageColor_[1].color = WHITE;
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
}

void PouseMode::ChackDraw()
{
	Novice::DrawSprite(330, 200, textFrameImage_, 1, 1, 0.0f, WHITE);
}
