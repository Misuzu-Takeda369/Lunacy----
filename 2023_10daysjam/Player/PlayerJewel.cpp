#include "PlayerJewel.h"

void PlayerJewel::Initialize(unsigned int& color)
{
	jewelstate_ = {
		{-200.0f,-200.0f},{0.0f,0.0f},0.0f,0.0f,color,
		Novice::LoadTexture("./Resources/images/AnimResources/PlayerAttackImage_kari.png")
	};
}

void PlayerJewel::Update(Vector2& pos, PlayerAttackType& playerAttackType, PlayerDirection& playerDurection)
{
	float dposX = pos.x;

	if (playerDurection== RIGHT) {
		dposX = pos.x - playerDistance_.x_;
	}
	else {
		dposX = pos.x + playerDistance_.x_;
	}
	
	jewelstate_.pos_ = { dposX ,pos.y- playerDistance_.y_ };

	if (playerAttackType == Magic) {
		jewelstate_.color_ = WHITE;
	}
	else {
		jewelstate_.color_ = 0x9E67FFFF;
	}
}

void PlayerJewel::Draw()
{
	Novice::DrawSprite(int(jewelstate_.pos_.x) - (imageSize_.x_/2), int(jewelstate_.pos_.y) - (imageSize_.y_ / 2), jewelstate_.image_,1.0f,1.0f,0.0f, jewelstate_.color_);
}
