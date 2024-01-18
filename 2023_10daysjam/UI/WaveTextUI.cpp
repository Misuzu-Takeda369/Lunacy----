﻿#include "WaveTextUI.h"

void WaveTextUI::Initialize(Wave& nowWave)
{
	//左上端
	Lpos_ = { 50,150 };
	//右下端
	Rpos_ = { sizeX_,sizeY_ };
	//画像
	image_ = Novice::LoadTexture("./Resources/images/Text/WaveLatter.png");


	nowWave_ = nowWave;
	nowWaveNum_ = (int)nowWave_;
}

void WaveTextUI::Update(Wave& nowWave)
{
	nowWave_ = nowWave;
	nowWaveNum_ = (int)nowWave_;
}

void WaveTextUI::Draw()
{
	Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + (sizeX_ * nowWaveNum_), 0, 125, sizeY_, image_, 0.25f, 1.0f, 0, WHITE);
}

void WaveTextUI::Draw(Vector2 ShakePos)
{

	Novice::DrawSpriteRect(Lpos_.x_ + int(ShakePos.x), Lpos_.y_ + int(ShakePos.y), 0 + (sizeX_ * nowWaveNum_), 0, 125, sizeY_, image_, 0.25f, 1.0f, 0, WHITE);

}
