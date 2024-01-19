#include "Apostel_MagicBall.h"
#include <Novice.h>
#include "Function/Function.h"
#include "ColorDefineEx.h"
#include"ScreenSize.h"

Apostel_MagicBall::~Apostel_MagicBall()
{
}

void Apostel_MagicBall::Initialize(CharaBase owner)
{
	charaBase_.pos_ = owner.pos_;
	float forceRand = (float)RandomRange(30, 60) * 0.001f;
	jumpForce_ = -(614.f - owner.pos_.y) * forceRand;
	//攻撃属性の決定
	attribute_ = Normal;
	charaBase_.color_ = RED;
	int attriRand = RandomRange(1, 100);
	if (attriRand <= 25) {
		attribute_ = Lunatic;
		charaBase_.color_ = BLUE; //CYANだとクッソ見づらい
	}
	int directionRand = RandomRange(1, 100);
	if(charaBase_.pos_.x<=200.f){}
	else if (directionRand <= 50||charaBase_.pos_.x>=1000.f) {
		moveDirection_ = -1;
	}
	collisionType_ = Circle;
	float sizeRand = (float)RandomRange(-5, 5);
	float spriteScalePlus = 0.015f * sizeRand;
	//spriteScale = 0.312f + spriteScalePlus;
	spriteScale = AdjustSpriteScale(64.f, 20.f + sizeRand);
	charaBase_.radius_ = 20.f + sizeRand; //弾の大きさ 20+ (-5～5)
	attackPoint_ += -sizeRand+(-sizeRand*0.5f+2.5f); //ダメージ30+((10～-5)
	//小さい方がダメージ量がでかい

	sprite_ = Novice::LoadTexture("./Resources/Images/apos_bullet.png");
	/*
	* 15～25
	* 1/20 = 0.05
	* 0.75～1.25
	* 64x64px sprite size
	* 64(sprite size)/20(default bullet size) = 3.2
	* 1/3.2 = 0.3125
	* 0.3125 * 0.05(=1/20)=0.015625
	* 0.2343～0.3906
	*/
}



void Apostel_MagicBall::Update()
{
	fallSpeed_ += 0.4f;
	charaBase_.pos_.y += fallSpeed_;
	if (charaBase_.pos_.y >= 614.f-charaBase_.radius_) {
		fallSpeed_ = jumpForce_;
		jumpForce_ *= 0.8f;
		if (jumpForce_ > -3.f) {
			jumpForce_ = -3.f;
		}
	}
	charaBase_.pos_.x += 4.f * float(moveDirection_);
	if (charaBase_.pos_.x >= kWindowWidth + charaBase_.radius_ ||
		charaBase_.pos_.x <= 0 - charaBase_.radius_) {
		isDead_ = true;
	}
}

void Apostel_MagicBall::Draw()
{
	
	Novice::DrawEllipse((int)charaBase_.pos_.x, (int)charaBase_.pos_.y, (int)charaBase_.radius_, (int)charaBase_.radius_, 0,
		charaBase_.color_, kFillModeWireFrame);
	DrawRotateScaleSprite(charaBase_.pos_, { 64.f,64.f }, 0, 0, sprite_, charaBase_.color_, spriteScale, 0);
}
