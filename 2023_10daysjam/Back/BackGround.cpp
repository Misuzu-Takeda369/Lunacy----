#include "BackGround.h"

void BackGround::Initialize()
{
	backImage_ = Novice::LoadTexture("./Resources/images/Back/bg1_.png");
	scaffoldImage_ = Novice::LoadTexture("./Resources/images/Back/ground.png");
	backLowSPImage_ = Novice::LoadTexture("./Resources/images/Back/bg1_lowSP.png");
	backMidiamSPImage_=Novice::LoadTexture("./Resources/images/Back/bg1_midiamSP.png");
	playerMaxSP_ = 500;
	playerSP_ = 500;
}

void BackGround::Update()
{
}

void BackGround::Draw()
{
	if (playerMaxSP_ / 4.5 > playerSP_) {
		Novice::DrawSprite(0, 0, backLowSPImage_, 1.0f, 1.0f, 0.0f, WHITE);
	}else if(playerMaxSP_/2>=playerSP_){
		Novice::DrawSprite(0, 0, backMidiamSPImage_, 1.0f, 1.0f, 0.0f, WHITE);
	}
	else {
		Novice::DrawSprite(0, 0, backImage_, 1.0f, 1.0f, 0.0f, WHITE);
	}
	Novice::DrawSprite(0, 614, scaffoldImage_, 1.0f, 1.0f, 0.0f, WHITE);
}

void BackGround::SetPlayerSP(float sp, float maxSP)
{
	playerMaxSP_ = (int)maxSP;
	playerSP_ = (int)sp;
}

void BackGround::Draw(Vector2 ShakePos)
{
	if (playerMaxSP_ / 4.5 > playerSP_) {
		Novice::DrawSprite(0, 0, backLowSPImage_, 1.0f, 1.0f, 0.0f, WHITE);
	}
	else if (playerMaxSP_ / 2 >= playerSP_) {
		Novice::DrawSprite(0, 0, backMidiamSPImage_, 1.0f, 1.0f, 0.0f, WHITE);
	}
	else {
		Novice::DrawSprite(0, 0, backImage_, 1.0f, 1.0f, 0.0f, WHITE);
	}
	//Novice::DrawSprite(0, 0, backImage_, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(0 + int(ShakePos.x), 614 + int(ShakePos.y), scaffoldImage_, 1.0f, 1.0f, 0.0f, WHITE);
}
