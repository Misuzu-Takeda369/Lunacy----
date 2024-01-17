#include "TimerUI.h"
#include "ColorDefineEx.h"

void TimerUI::Initialize()
{
	timerUIPos_ = { 50,650 };
	timer_ = 1800.0f;
	timerDisplay_ = int(timer_) / 60;
	timerMaxDis_ = 60;

	color_.color = YELLOW;

	//左端
	Lpos_ = { timerUIPos_ };
	//右端
	Rpos_ = { sizeX_,sizeY_ };
	//画像
	image_ = Novice::LoadTexture("./Resources/images/UI/HPBar_2.png");
	frameImage_ = Novice::LoadTexture("./Resources/images/UI/Timer&BossFrame.png");

	//移動した合計
	moveX_ = 0;
	
	moveSpeedX_ = 17;
}

void TimerUI::Update()
{
	timer_--;
	timerDisplay_ = int(timer_) / 60;

	ConversionUIVer2();
	//ConversionUIVer1();

	if (timer_ <= 0.0f) {
		timer_ = 0.0f;
		moveX_ = 0;
	}

}

void TimerUI::Update(Wave nowWave)
{
	if ((nowWave != Tutorial) && (nowWave != Wave4)) {
		timer_--;
	}

	timerDisplay_ = int(timer_ )/ 60;

	ConversionUIVer2();
	//ConversionUIVer1();

	if (timer_ <= 0) {
		timer_ = 0;
		moveX_ = 0;
	}


#pragma region ImGum関連

#ifdef _DEBUG
	ImGui::Begin("Timer");

	ImGui::Text("timerDisplay_: %d\n", timerDisplay_);

	ImGui::End();
#endif // DEBUG

#pragma endregion
}

void TimerUI::Draw()
{

#ifdef _DEBUG
	Novice::ScreenPrintf(timerUIPos_.x_, timerUIPos_.y_, "Timer: %d", timerDisplay_);
#endif // _DEBUG

	//決まった範囲に画像写すタイプ
	Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + moveX_, 0, sizeX_, sizeY_, image_, ((float)500 / 1000), 0.5, 0, color_.color);
	//画像写す範囲を徐々に狭めていくタイプ
	//Novice::DrawQuad(Lpos_.x_, Lpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_, Lpos_.x_, Lpos_.y_ + Rpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_ + Rpos_.y_
		//, 0, 0, sizeX_, sizeY_, image_, WHITE);

	//フレーム
	Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0, 0, sizeX_, sizeY_, frameImage_, ((float)500 / 1000), 1.0, 0, WHITE);


}

void TimerUI::Draw(Vector2 ShakePos)
{
	//決まった範囲に画像写すタイプ
	Novice::DrawSpriteRect(Lpos_.x_ + int(ShakePos.x), Lpos_.y_ + int(ShakePos.y), 0 + moveX_, 0, sizeX_, sizeY_, image_, ((float)500 / 1000), 0.5, 0, color_.color);
	//画像写す範囲を徐々に狭めていくタイプ
	//Novice::DrawQuad(Lpos_.x_, Lpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_, Lpos_.x_, Lpos_.y_ + Rpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_ + Rpos_.y_
		//, 0, 0, sizeX_, sizeY_, image_, WHITE);

	//フレーム
	Novice::DrawSpriteRect(Lpos_.x_ + int(ShakePos.x), Lpos_.y_ + int(ShakePos.y), 0, 0, sizeX_, sizeY_, frameImage_, ((float)500 / 1000), 1.0, 0, WHITE);

}

void TimerUI::ConversionUIVer1()
{

	int timer = timerMaxDis_ - timerDisplay_;
	moveX_ = (moveSpeedX_)*timer;
}

void TimerUI::ConversionUIVer2()
{
	if (fmod(timer_,0.277f)== 0) {

		moveX_ += 1;
	}
}
