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
	collisionType_ = Circle;
	t_ = 0;
}

void Apostel_ThrowMine::Update()
{
	t_ += 1.f / 30.f;
	if (t_ > 1) {
		t_ = 1;
	}
	if (charaBase_.pos_.y < groundLevel_) {
		charaBase_.pos_.x = (1.0f - t_) * start_.x + t_ * target_.x;
		charaBase_.pos_.y = (1.0f - t_) * start_.y + t_ * target_.y;
	}
	else {
		charaBase_.pos_.y = groundLevel_;
		timeCounter_++;
	}
	
}

void Apostel_ThrowMine::Draw()
{
	Novice::DrawEllipse((int)charaBase_.pos_.x, (int)charaBase_.pos_.y,
		(int)charaBase_.radius_,(int) charaBase_.radius_, 0, ORANGE,kFillModeSolid);
}
