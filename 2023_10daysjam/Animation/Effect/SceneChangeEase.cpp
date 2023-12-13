#include "SceneChangeEase.h"
#include "Function/Easing.h"

void SceneChangeEase::Initialize()
{
	//■の左端位置
	pos_ = {0,0};

	//■を徐々に
	scale_= mimScale;
	
	//念のための色
	color_.color = 0xFFFFFFFF;
}

void SceneChangeEase::Update()
{
	if (scale_ >= maxScale) {
		scale_ = Easeing(scale_, __EaseOutCubic);
	}
	

}

void SceneChangeEase::Draw()
{
	Novice::DrawBox(pos_.x_, pos_.y_,size_* int(scale_), size_ * int(scale_),0.0f, color_.color,kFillModeSolid);
	
}
