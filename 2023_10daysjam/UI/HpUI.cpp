#include "HpUI.h"

void HpUI::Initialize()
{
	//左上端
	Lpos_ = { 50,20 };
	//右下端
	Rpos_ = { sizeX_,sizeY_ };
	//画像
	image_ = Novice::LoadTexture("./Resources/images/UI/HPBar_2.png");
	frameImage_ = Novice::LoadTexture("./Resources/images/UI/HPBar_box2.png");
	//移動した合計
	moveX_ = 0;
	//移動する量(HPが1たび増減するたびに動く量)
	moveSpeedX_ = 1;

	color_.color = GREEN;
	color_.R = 0;
	color_.B = 0;
	color_.G = 255;
	color_.A = 255;
}

void HpUI::Update(float decreasedHp)
{

	int decreaseHp = int(decreasedHp);
	moveX_ = (moveSpeedX_)*decreaseHp;

	//一応回復しない前提
	if (preValue != decreaseHp) {
		float rate = decreaseHp / 500.f;
		float preRate = preValue / 500.f;
		int ratePercentage = int(rate * 100.f);
		int preRatePercentage = int(preRate * 100.f);
		int num = ratePercentage - preRatePercentage;

		if (color_.R < 255) {
			color_.R += int(4.5f) * num;
			if (color_.R >= 255) {
				color_.R = 255;
			}
		}
		else {
			color_.R = 255;
			if (color_.G > 0) {
				color_.G -= int(8.5f) * num;
				if (color_.G <= 0) {
					color_.G = 0;
				}
			}
			else {
				color_.G = 0;
			}
		}

	}
	color_.color = GetColorValue(color_.R, color_.G, color_.B, color_.A);
	preValue = decreaseHp;
}


void HpUI::Draw()
{
	//決まった範囲に画像写すタイプ
	//Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + moveX_, 0, sizeX_-1, sizeY_, image_, ((float)500 / 1000), 1, 0, WHITE);
	//画像写す範囲を徐々に狭めていくタイプ
	Novice::DrawQuad(Lpos_.x_, Lpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_, Lpos_.x_, Lpos_.y_ + Rpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_ + Rpos_.y_
		, 0, 0, sizeX_, sizeY_, image_, color_.color);

	//フレーム
	Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_,0,0, 0, sizeY_, frameImage_, ((float)500 / 1000),1,0,WHITE);
}

void HpUI::Draw(Vector2 ShakePos)
{
	//決まった範囲に画像写すタイプ
	//Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + moveX_, 0, sizeX_-1, sizeY_, image_, ((float)500 / 1000), 1, 0, WHITE);
	//画像写す範囲を徐々に狭めていくタイプ
	Novice::DrawQuad(Lpos_.x_ + int(ShakePos.x), Lpos_.y_ + int(ShakePos.y), (Lpos_.x_ + Rpos_.x_) + int(ShakePos.x) - moveX_, Lpos_.y_ + int(ShakePos.y), Lpos_.x_ + int(ShakePos.x), Lpos_.y_ + Rpos_.y_ + int(ShakePos.y), (Lpos_.x_ + Rpos_.x_) + int(ShakePos.x) - moveX_, Lpos_.y_ + Rpos_.y_ + int(ShakePos.y)
		, 0, 0, sizeX_, sizeY_, image_, color_.color);

	//フレーム
	Novice::DrawSpriteRect(Lpos_.x_+int(ShakePos.x), Lpos_.y_ + int(ShakePos.y), 0, 0, sizeX_, sizeY_, frameImage_, ((float)500 / 1000), 1, 0, WHITE);

}

