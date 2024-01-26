#include "Apostel_ThrowMine.h"
#include <Novice.h>
#include "ColorDefineEx.h"
#include "Function/Function.h"
#include <algorithm>

void Apostel_ThrowMine::Initialize(CharaBase owner, Vector2 playerPos)
{
	charaBase_.pos_ = owner.pos_;
	start_ = owner.pos_;
	target_.x = playerPos.x;
	target_.y = groundLevel_;
	charaBase_.radius_ = baseRadius_;
	isActive_ = false;
	isDead_ = false;
	timeCounter_ = 0;
	if (owner.pos_.x > playerPos.x) {
		moveDirection_ = 1;
	}
	else {
		moveDirection_ = -1;
	}
	collisionType_ = Circle;
	t_ = 0;
	blinkingTimer_ = 0;
	blinking_ = true;

	//時限爆弾爆発
	timeBombExplosionEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/mini_bomb1.wav");
	//時限爆弾爆発
	timeBombExplosionPlay_ = 0;

	//sprite
	sprite_ = Novice::LoadTexture("./Resources/Images/AnimResources/mine.png");
	theta_ = 0;
	rotateSpeed_ = (float)RandomRange(3, 9) * 0.1f;
	effect_ = Novice::LoadTexture("./Resources/Images/AnimResources/mine_light.png");
	effectFlag_ = false;
	effectTheta_ = 0;
	effectScale_ = 0;
	effectScaleFlag_ = false;
	effectScaleSpeed_ = 0;

	bombEffect_ = Novice::LoadTexture("./Resources/Images/AnimResources/bomb.png");
	bombRadius_ = 0;
}

void Apostel_ThrowMine::Update()
{
	t_ += 1.f / 30.f;
	if (t_ > 1) {
		t_ = 1;
	}
	
	
	//攻撃が広がる
	if (isActive_) {

		if (Novice::IsPlayingAudio(timeBombExplosionPlay_) == 0) {
			timeBombExplosionPlay_ = Novice::PlayAudio(timeBombExplosionEffect_, 0, 0.8f);
		}

		charaBase_.color_ = WHITE;
		charaBase_.radius_+=6;
		if (charaBase_.radius_ >= maxRadius_) {
			isDead_ = true;
		}
		bombRadius_ = AdjustSpriteScale(128.f, charaBase_.radius_);
		blinking_ = true;
	}
	else {
		if (charaBase_.pos_.y < groundLevel_) {
			charaBase_.pos_.x = (1.0f - t_) * start_.x + t_ * target_.x;
			charaBase_.pos_.y = (1.0f - t_) * start_.y + t_ * target_.y;
			theta_ += rotateSpeed_;
		}
		else {
			charaBase_.pos_.y = groundLevel_ + 1;
			timeCounter_++;
			blinkingTimer_++;
			if (blinkingTimer_ >= 3) {
				if (blinking_) {
					blinking_ = false;
				}
				else {
					blinking_ = true;
				}
				blinkingTimer_ = 0;
			}
			if (timeCounter_ >= (baseActiveTime_ - 10)) {
				effectFlag_ = true;
			}
		}
		charaBase_.color_ = 0x00000000;
	}
	//一定時間で起爆
	if (timeCounter_ >= baseActiveTime_) {
		isActive_ = true;
		effectFlag_ = false;
	}

	if (effectFlag_) {
		effectTheta_ += 0.23f;
		if (!effectScaleFlag_) {
			effectScaleSpeed_ += 0.1f;
			effectScale_ += effectScaleSpeed_;
			if (effectScale_ >= 0.5f) {
				effectScaleFlag_ = true;
			}
		}
		else {
			effectScale_ = std::clamp(effectScale_ - 0.05f, 0.0f, 0.5f);
		}
	}
	
}

void Apostel_ThrowMine::Draw()
{
	if (blinking_) {
		DrawRotateScaleSprite(charaBase_.pos_, { 128.f,128.f }, 0, 0, sprite_, WHITE, 0.25f, theta_);
		//Novice::DrawEllipse((int)charaBase_.pos_.x, (int)charaBase_.pos_.y,
		//	(int)charaBase_.radius_, (int)charaBase_.radius_, 0, charaBase_.color_, kFillModeSolid);
		DrawRotateScaleSprite(charaBase_.pos_, { 128.f,128.f }, 0, 0, bombEffect_, charaBase_.color_, bombRadius_, 0);
	}
	if (effectFlag_) {
		DrawRotateScaleSprite(charaBase_.pos_, { 128.f,128.f }, 0, 0, effect_, WHITE, effectScale_, effectTheta_);
	}
}
