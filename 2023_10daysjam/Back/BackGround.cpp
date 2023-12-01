#include "BackGround.h"

void BackGround::Initialize()
{
	backImage_ = Novice::LoadTexture("./Resources/images/Back/bg1_.png");
	scaffoldImage_ = Novice::LoadTexture("./Resources/images/Back/ground.png");
}

void BackGround::Update()
{
}

void BackGround::Draw()
{
	Novice::DrawSprite(0,0, backImage_,1.0f, 1.0f,0.0f,WHITE);
	Novice::DrawSprite(0, 614, scaffoldImage_, 1.0f, 1.0f, 0.0f, WHITE);
}
