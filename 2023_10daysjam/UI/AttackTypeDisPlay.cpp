#include "AttackTypeDisPlay.h"

void AttackTypeDisPlay::Initialize()
{
	//現在の攻撃タイプ
	playerAttackTypeNow_;

	//画像の位置
	imagePos_ = {0,0};

	//初期位置
	setPos_ = {230,150};


	//画像
	Image_ = Novice::LoadTexture("./Resources/images/Text/AttackStale.png");
	imageNum_ = 0;
}

void AttackTypeDisPlay::Update(PlayerAttackType& now)
{
	if (now == Magic) {

		imageNum_ = 1;
	}
	else {
		imageNum_ = 0;
	}

	imagePos_.x_ = size_.x_ * imageNum_;
}

void AttackTypeDisPlay::Draw()
{
	Novice::DrawSpriteRect(setPos_.x_, setPos_.y_, imagePos_.x_,imagePos_.y_, size_.x_, size_.y_, Image_,0.5f,1.0f,0.0f,WHITE);

	//Novice:: DrawBox(setPos_.x_, setPos_.y_,100,100,0.0f,WHITE,kFillModeSolid);
}
