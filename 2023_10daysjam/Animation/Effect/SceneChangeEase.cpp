#include "SceneChangeEase.h"
#include "Function/Easing.h"
#include "ScreenSize.h"

void SceneChangeEase::Initialize()
{
	//■の左端位置
	pos_ = { 0,0 };

	////■を徐々に
	scale_= mimScale;
	
	//念のための色
	color_.color = 0x000000FF;

	size_ = 10 * mimScale;
}

void SceneChangeEase::Update()
{

	/*if (nowEffectMode_ == Before) {
		ChangeBefore();
	}
	else if (nowEffectMode_ == After) {
		ChangeAfter();
	}*/
	
	//多分いらんくなった個別にやった方が楽(個人的)

}

void SceneChangeEase::Draw()
{
	Novice::DrawBox(pos_.x_, pos_.y_, size_, size_,0.0f, color_.color,kFillModeSolid);
	
}

void SceneChangeEase::ChangeBefore()
{
	if (scale_ <= maxScale) {
		//scale_ += int(10.0 +Easeing(scale_, __EaseOutCubic));
		scale_ += 10;
		//scale_ += 10 * int (Easeing(float(scale_), __EaseOutCubic));
	}
	else {
	  nowEffectMode_ = After;
	}
	
	size_ = 10 * scale_;
}

void SceneChangeEase::ChangeAfter()
{
	if (scale_ >= mimScale) {
		//scale_ -= float(1.0 + Easeing(scale_, __EaseOutCubic));
		scale_ -= 10;
		//scale_ -= 10 * int(Easeing(float(scale_), __EaseOutCubic));
	}
	else {
		nowEffectMode_ = Nochange;
	}

	size_ = 10 * scale_;
}
