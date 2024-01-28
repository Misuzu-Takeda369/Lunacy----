#include "HitEffect.h"
#include <algorithm>
#include "Function/Function.h"


void HitEffect::Initialize()
{
	Shakepos_ = { 0,0 };

	color_.color = 0x00000000;

	shakeFlag_ = false;
	randNum_ = 10;
	shakeFrame_ = 30;

	psychoDamageEffect_[0] = Novice::LoadTexture("./Resources/Images/Back/SPdamage1.png");
	psychoDamageEffect_[1] = Novice::LoadTexture("./Resources/Images/Back/SPdamage2.png");
	SPColor_.color = WHITE;
}

void HitEffect::OnColistion(EnemyType type)
{
	shakeFlag_ = true;
	type_ = type;
	SPColor_.color = 0xFFFFFFFF;
	SPColor_.A = 255;
}


void HitEffect::Update()
{
	if (shakeFlag_) {

		//後で色調整
		if (type_ == SPNOMAL) {
			SPColor_.A = std::clamp(SPColor_.A - 10, 0, 255);
			SPColor_.color = GetColorValue(255, 255, 255, SPColor_.A);
			color_.color = 0x19197070;
		}
		else {
			color_.color = 0xB01B1780;
		}

		shakeFrame_--;


		Shakepos_.x = 2.0f * float(RandomRange(-randNum_, randNum_));
		Shakepos_.y = 3.0f * float(RandomRange(-randNum_, randNum_));

		if (shakeFrame_ % 6 == 0) {
			randNum_--;
		}

		if (randNum_ <= 0) {
			shakeFlag_ = false;
			randNum_ = 10;
			Shakepos_ = { 0.0f,0.0f };

			color_.color = 0x00000000;
			SPColor_.color = 0x00000000;
		}
	}
}

void HitEffect::Draw()
{
	if (type_ == HPNOMAL || type_ == NONE) {
		Novice::DrawBox(MimWindowWidth, MimWindowHeight, kWindowWidth, kWindowHeight, 0.0f, color_.color, kFillModeSolid);
	}
	else {
		Novice::DrawBox(MimWindowWidth, MimWindowHeight, kWindowWidth, kWindowHeight, 0.0f, color_.color, kFillModeSolid);
		if (500.f / 4.f < playerSP_) {
			Novice::DrawSprite(MimWindowWidth, MimWindowHeight, psychoDamageEffect_[0], 1, 1, 0, SPColor_.color);
		}
		else {
			Novice::DrawSprite(MimWindowWidth, MimWindowHeight, psychoDamageEffect_[1], 1, 1, 0, SPColor_.color);
		}
	}
}

void HitEffect::SetPlayerSP(float sp)
{
	playerSP_ = sp;
}

