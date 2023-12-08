#include "Apostel_ThrowMine.h"
#include <Novice.h>
#include "ColorDefineEx.h"

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
}

void Apostel_ThrowMine::Update()
{
	t_ += 1.f / 30.f;
	if (t_ > 1) {
		t_ = 1;
	}
	
	
	//攻撃が広がる
	if (isActive_) {
		charaBase_.color_ = ORANGE;
		charaBase_.radius_+=6;
		if (charaBase_.radius_ >= maxRadius_) {
			isDead_ = true;
		}
		blinking_ = true;
	}
	else {
		if (charaBase_.pos_.y < groundLevel_) {
			charaBase_.pos_.x = (1.0f - t_) * start_.x + t_ * target_.x;
			charaBase_.pos_.y = (1.0f - t_) * start_.y + t_ * target_.y;
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
		}
		charaBase_.color_ = MAGENTA;
	}
	//一定時間で起爆
	if (timeCounter_ >= baseActiveTime_) {
		isActive_ = true;
	}
	
}

void Apostel_ThrowMine::Draw()
{
	if (blinking_) {
		Novice::DrawEllipse((int)charaBase_.pos_.x, (int)charaBase_.pos_.y,
			(int)charaBase_.radius_, (int)charaBase_.radius_, 0, charaBase_.color_, kFillModeSolid);
	}
}
