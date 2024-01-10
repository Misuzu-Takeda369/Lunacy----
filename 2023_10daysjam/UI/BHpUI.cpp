#include "BHpUI.h"

void BHpUI::Initialize()
{
	bossHpUIPos_ = { 50,650 };
	hp_ = 100;
	
	bossHpDisplay_ = 60;

	color_.color = 0xE756FFFF;

	//左端
	Lpos_ = { bossHpUIPos_ };
	//右端
	Rpos_ = { sizeX_,sizeY_ };
	//画像
	image_ = Novice::LoadTexture("./Resources/images/UI/HPBar_2.png");
	frameImage_ = Novice::LoadTexture("./Resources/images/UI/Timer&BossFrame.png");

	//移動した合計
	moveX_ = 0;
	//移動する量(HPが1減るたびに動く量)
	moveSpeedX_ = 1;
}

void BHpUI::Update(int decreasedHp)
{
	//hp_ = int(decreasedHp);
	hp_ = int(decreasedHp) + keepstate;
	//moveX_ = (moveSpeedX_)*hp_;

	if (hp_ %2 == 0) {
		moveX_ = (moveSpeedX_)*hp_;
		keepstate = 0;
	}
	else {
		hp_--;
		moveX_ = (moveSpeedX_)*hp_;
		keepstate = 1;
	}
	

	//ConversionUIVer2();
	//ConversionUIVer1();

	if (hp_ <= 0) {
		hp_ = 0;
		moveX_ = 0;
	}
}

void BHpUI::Draw(Vector2 ShakePos)
{
	//決まった範囲に画像写すタイプ
	Novice::DrawSpriteRect(Lpos_.x_ + int(ShakePos.x), Lpos_.y_ + int(ShakePos.y), 0 + moveX_, 0, sizeX_, sizeY_, image_, ((float)500 / 1000), 0.5, 0, color_.color);
	//画像写す範囲を徐々に狭めていくタイプ
	//Novice::DrawQuad(Lpos_.x_, Lpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_, Lpos_.x_, Lpos_.y_ + Rpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_ + Rpos_.y_
		//, 0, 0, sizeX_, sizeY_, image_, WHITE);

	//フレーム
	Novice::DrawSpriteRect(Lpos_.x_ + int(ShakePos.x), Lpos_.y_ + int(ShakePos.y), sizeX_, 0, sizeX_, sizeY_, frameImage_, ((float)500 / 1000), 1.0, 0, WHITE);

}

void BHpUI::ConversionUIVer2()
{
	if (hp_ % 5 == 0) {

		moveX_ += 1;
	}
}
