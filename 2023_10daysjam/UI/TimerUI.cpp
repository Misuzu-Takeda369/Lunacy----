#include "TimerUI.h"

void TimerUI::Initialize()
{
	timerUIPos_ = {50,650};
	timer_ = 3600;
	timerDisplay_ = timer_/60;
	timerMaxDis_ = 60;


	//左端
	Lpos_ = { timerUIPos_ };
	//右端
	Rpos_ = { sizeX_,sizeY_ };
	//画像
	image_ = Novice::LoadTexture("./Resources/images/UI/HPBar_kari.png");

	//移動した合計
	moveX_ = 0;
	//移動する量(HPが1減るたびに動く量)
	moveSpeedX_ = 8;
}

void TimerUI::Update()
{
	timer_--;
	timerDisplay_ = timer_ / 60;
	
	ConversionUIVer2();
	//ConversionUIVer1();

	if (timer_<= 0) {
		timer_ = 0;
		moveX_ = 0;
	}

}

void TimerUI::Update(Wave nowWave)
{
	if ((nowWave != Tutorial)&&(nowWave != Wave4)) {
		timer_--;
	}
	
	timerDisplay_ = timer_ / 60;

	ConversionUIVer2();
	//ConversionUIVer1();

	if (timer_ <= 0) {
		timer_ = 0;
		moveX_ = 0;
	}

}

void TimerUI::Draw()
{

#ifdef _DEBUG
	Novice::ScreenPrintf(timerUIPos_.x_, timerUIPos_.y_,"Timer: %d", timerDisplay_);
#endif // _DEBUG

	//決まった範囲に画像写すタイプ
	Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + moveX_, 0, sizeX_, sizeY_, image_, ((float)500 / 1000), 0.5, 0, WHITE);
	//画像写す範囲を徐々に狭めていくタイプ
	//Novice::DrawQuad(Lpos_.x_, Lpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_, Lpos_.x_, Lpos_.y_ + Rpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_ + Rpos_.y_
		//, 0, 0, sizeX_, sizeY_, image_, WHITE);


}

void TimerUI::ConversionUIVer1()
{

	int timer = timerMaxDis_ - timerDisplay_;
	moveX_ = (moveSpeedX_)*timer;
}

void TimerUI::ConversionUIVer2()
{
	if (timer_%7 == 0) {
		
		moveX_ += 1;
	}
}
