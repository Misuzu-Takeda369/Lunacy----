#include "HitEffect.h"


void HitEffect::Initialize()
{
	Shakepos_ = {0,0};

	color_.color = 0x00000000;

	shakeFlag_ = false;
	randNum_ = 10;
	shakeFrame_ = 30;
}

void HitEffect::OnColistion()
{
	shakeFlag_ = true;
}


void HitEffect::Update()
{
	if (shakeFlag_) {

		//後で色調整
		color_.color = 0xB01B1780;

		shakeFrame_--;

		Shakepos_.x = 2.0f*float(RandomRange(-randNum_, randNum_));
		Shakepos_.y = 3.0f * float(RandomRange(-randNum_, randNum_));

		if (shakeFrame_%6 == 0) {
			randNum_--;
		}

		if (randNum_ <= 0) {
			shakeFlag_ = false;
			randNum_ = 10;
			Shakepos_ = {0.0f,0.0f };

			color_.color = 0x00000000;
		}
	}
}

void HitEffect::Draw()
{
	Novice::DrawBox(MimWindowWidth, MimWindowHeight, kWindowWidth, kWindowHeight,0.0f, color_.color,kFillModeSolid);
}

