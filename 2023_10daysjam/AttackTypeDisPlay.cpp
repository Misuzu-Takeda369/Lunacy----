#include "AttackTypeDisPlay.h"

void AttackTypeDisPlay::Initialize()
{
	//現在の攻撃タイプ
	playerAttackTypeNow_;

	//画像の位置
	imagePos_ = { size_.x_* 0,0};

	//初期位置
	IntState setPos_ = {500,400};


	//画像
	int Image_ = Novice::LoadTexture("./Resources/images/Text/MindStale.png");
}

void AttackTypeDisPlay::Update(PlayerAttackType& now)
{
}

void AttackTypeDisPlay::Draw()
{
	Novice::DrawSpriteRect(setPos_.x_, setPos_.y_, imagePos_.x_,imagePos_.y_, 1, 1, Image_,1.0f,1.0f,0.0f,WHITE);
}
