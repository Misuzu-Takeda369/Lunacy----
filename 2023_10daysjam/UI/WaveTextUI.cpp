﻿#include "WaveTextUI.h"

void WaveTextUI::Initialize(Wave& nowWave)
{
	//左上端
	Lpos_ = { 50,150 };
	//右下端
	Rpos_ = { sizeX_,sizeY_ };
	//画像
	image_ = Novice::LoadTexture("./Resources/images/Text/WaveLatter_kari.png");
	//移動した合計
	moveX_ = 0;
	//移動する量(HPが1たび増減するたびに動く量)
	moveSpeedX_ = 1;

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
	Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + (sizeX_* nowWaveNum_), 0, sizeX_, sizeY_, image_, 0.25, 1, 0, WHITE);
}