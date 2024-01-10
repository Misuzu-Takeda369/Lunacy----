#include "EHpUI.h"

//void EHpUI::Initialize(Vector2 pos, int moveSpeedX)
//{
//	//左上端
//	Lpos_ = { int(pos.x) - 32,int(pos.y) - 64 };
//	//右下端
//	Rpos_ = { sizeX_,sizeY_ };
//	//画像
//	//image_ = Novice::LoadTexture("./Resources/images/UI/HpBarMini_kari.png");
//	
//	
//	//移動した合計
//	moveX_ = 0;
//	//移動する量(HPが1たび増減するたびに動く量)
//	moveSpeedX_ = moveSpeedX; 
//}

void EHpUI::Initialize(Vector2 pos, float Hp)
{
	//左上端
	Lpos_ = { int(pos.x) - 32,int(pos.y) - 64 };
	//右下端
	Rpos_ = { sizeX_,sizeY_ };

	nowHp_ = int(Hp);
}



//void EHpUI::Update(float decreasedHp, Vector2 pos)
//{
//
//	左上端
//	Lpos_ = { int(pos.x)-32,int(pos.y)-64 };
//
//	
//	int decreaseHp = int(decreasedHp);
//	moveX_ = (moveSpeedX_)*decreaseHp;
//}

void EHpUI::Update(float Hp, Vector2 pos)
{

	nowHp_ = int(Hp);
	//左上端
	Lpos_ = { int(pos.x) - 32,int(pos.y) - (64+ sizeY_) };

	EnemyHpToImageNum();
	
}

void EHpUI::Draw()
{
	//決まった範囲に画像写すタイプ
	//Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + moveX_, 0, sizeX_-1, sizeY_, image_, ((float)500 / 1000), 1, 0, WHITE);

	Novice::DrawQuad(Lpos_.x_, Lpos_.y_,Lpos_.x_ + Rpos_.x_, Lpos_.y_, Lpos_.x_, Lpos_.y_ + Rpos_.y_, Lpos_.x_ + Rpos_.x_, Lpos_.y_ + Rpos_.y_
		, sizeX_ * numX_[0], sizeY_ * numY_[0], sizeX_, sizeY_, image_, WHITE);

	Novice::DrawQuad(Lpos_.x_ + sizeX_, Lpos_.y_, Lpos_.x_ + Rpos_.x_ + sizeX_, Lpos_.y_, Lpos_.x_ + sizeX_, Lpos_.y_ + Rpos_.y_, Lpos_.x_ + Rpos_.x_ + sizeX_, Lpos_.y_ + Rpos_.y_
		, sizeX_ * numX_[1], sizeY_ * numY_[1], sizeX_, sizeY_, image_, WHITE);

	Novice::DrawQuad(Lpos_.x_ + (sizeX_*2), Lpos_.y_, Lpos_.x_ + Rpos_.x_ + (sizeX_ * 2), Lpos_.y_, Lpos_.x_ + (sizeX_ * 2), Lpos_.y_ + Rpos_.y_, Lpos_.x_ + Rpos_.x_ + (sizeX_ * 2), Lpos_.y_ + Rpos_.y_
		, sizeX_ * numX_[2], sizeY_ * numY_[2], sizeX_, sizeY_, image_, WHITE);

	//Novice::DrawSprite(Lpos_.x_, Lpos_.y_, image_ , 0.5, 1, 0.0f, WHITE);

	
}

void EHpUI::EnemyHpToImageNum()
{
	int Num = nowHp_;


	HpDigitDraw_[0] = Num / 100;
	Num %= 100;

	HpDigitDraw_[1] = Num / 10;
	Num %= 10;

	HpDigitDraw_[2] = Num / 1;
	Num %= 1;

	Num = nowHp_;

#pragma region 画像の数字の位置
	for (int i = 0; i < 3; i++) {
		///X
		if (HpDigitDraw_[i] == 0 || HpDigitDraw_[i] == 5) {
			numX_[i] = 0;
		}
		else if (HpDigitDraw_[i] == 1 || HpDigitDraw_[i] == 6) {
			numX_[i] = 1;
		}
		else if (HpDigitDraw_[i] == 2 || HpDigitDraw_[i] == 7) {
			numX_[i] = 2;
		}
		else if (HpDigitDraw_[i] == 3 || HpDigitDraw_[i] == 8) {
			numX_[i] = 3;
		}
		else {
			numX_[i] = 4;
		}

		///Y
		if (HpDigitDraw_[i] <= 4) {
			numY_[i] = 0;
		}
		else {
			numY_[i] = 1;
		}
	}

#pragma endregion
}
