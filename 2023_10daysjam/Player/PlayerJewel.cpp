#include "PlayerJewel.h"

PlayerJewel::~PlayerJewel()
{
	delete atdp_;
}

void PlayerJewel::Initialize(unsigned int& color)
{
	jewelstate_ = {
		{-200.0f,-200.0f},{0.0f,0.0f},0.0f,0.0f,color,
		Novice::LoadTexture("./Resources/images/AnimResources/PlayerAttackImage.png")
	};

	atdp_ = new AttackTypeDisPlay();
	atdp_->Initialize();

}

void PlayerJewel::Update(Vector2& pos, PlayerAttackType& playerAttackType, PlayerDirection& playerDurection)
{
	float dposX = pos.x;

	if (playerDurection== RIGHT) {
		dposX = pos.x - playerDistance_.x_;
	}
	else {
		dposX = pos.x + (playerDistance_.x_*1.5f);
	}
	
	jewelstate_.pos_ = { dposX ,pos.y- playerDistance_.y_ };

	if (playerAttackType == Magic) {
		jewelstate_.color_ = WHITE;
	}
	else {
		jewelstate_.color_ = 0x9E67FFFF;
	}

	atdp_->Update(playerAttackType);
}

void PlayerJewel::Draw()
{
	Novice::DrawSprite(int(jewelstate_.pos_.x) - (imageSize_.x_), int(jewelstate_.pos_.y) - (imageSize_.y_ / 2), jewelstate_.image_,1.0f,1.0f,0.0f, jewelstate_.color_);

	atdp_->Draw();
}
