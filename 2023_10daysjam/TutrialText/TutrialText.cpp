#include "TutrialText.h"

void TutrialText::Initialize()
{
	textFrameImage_ = Novice::LoadTexture("./Resources/images/Back/Textfream.png");
	textImage_ = Novice::LoadTexture("./Resources/images/Text/Text.png");

	imageNum_ = 0;
	DisplayNum = {
		0 , 0
	};
}

void TutrialText::Update()
{
	switch (imageNum_)
	{
	case 0:
		DisplayNum = {
		0 , 0
		};

		break;
	case 1:

		DisplayNum = {
		 1,0
		};
		break;
	case 2:
		DisplayNum = {
		 2,0
		};

		break;
	case 3:
		DisplayNum = {
		 3,0
		};
		break;
	case 4:
		DisplayNum = {
		 0,1
		};

		break;
	case 5:
		DisplayNum = {
		1 , 1
		};
		break;
	case 6:

		DisplayNum = {
		2,1
		};
		break;
	case 7:
		DisplayNum = {
		3,1
		};
		break;
	case 8:

		DisplayNum = {
		0,2
		};
		break;
	case 9:

		DisplayNum = {
		1,2
		};
		break;
	case 10:

		DisplayNum = {
		2,2
		};
		break;
	case 11:

		DisplayNum = {
		3,2
		};

		break;

	default:
		break;
	}
}

void TutrialText::Draw()
{
	Novice::DrawSprite(580, 150, textFrameImage_, 1, 1, 0.0f, WHITE);
	//Novice::DrawSprite(580, 150, textImage_, 1, 1, 0.0f, WHITE);
	Novice::DrawQuad(580, 150, 580 + imageSize_.x_, 150, 580, 150 + imageSize_.y_, 580 + imageSize_.x_, 150 + imageSize_.y_,
		imageSize_.x_ * DisplayNum.x_, imageSize_.y_ * DisplayNum.y_, imageSize_.x_, imageSize_.y_, textImage_, WHITE);
}
