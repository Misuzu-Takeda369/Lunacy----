#include "EHpUI.h"

void EHpUI::Initialize(Vector2 pos, int moveSpeedX)
{
	//左上端
	Lpos_ = { int(pos.x) - 32,int(pos.y) - 64 };
	//右下端
	Rpos_ = { sizeX_,sizeY_ };
	//画像
	image_ = Novice::LoadTexture("./Resources/images/UI/HpBarMini_kari.png");
	//frameImage_ = Novice::LoadTexture("./Resources/images/UI/HPBar_box2.png");
	//移動した合計
	moveX_ = 0;
	//移動する量(HPが1たび増減するたびに動く量)
	moveSpeedX_ = moveSpeedX; 
}

void EHpUI::Update(float decreasedHp, Vector2 pos)
{

	//左上端
	Lpos_ = { int(pos.x)-32,int(pos.y)-64 };

	
	int decreaseHp = int(decreasedHp);
	moveX_ = (moveSpeedX_)*decreaseHp;
}

void EHpUI::Draw()
{
	//決まった範囲に画像写すタイプ
	//Novice::DrawSpriteRect(Lpos_.x_, Lpos_.y_, 0 + moveX_, 0, sizeX_-1, sizeY_, image_, ((float)500 / 1000), 1, 0, WHITE);

	Novice::DrawQuad(Lpos_.x_, Lpos_.y_, (Lpos_.x_ + Rpos_.x_)- moveX_, Lpos_.y_, Lpos_.x_, Lpos_.y_ + Rpos_.y_, (Lpos_.x_ + Rpos_.x_) - moveX_, Lpos_.y_ + Rpos_.y_
		, 0, 0, sizeX_, sizeY_, image_, WHITE);

	//Novice::DrawSprite(Lpos_.x_, Lpos_.y_, image_ , 0.5, 1, 0.0f, WHITE);
}
