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
	charaBase_.radius_ = 20.f + sizeRand; //弾の大きさ 20+ (-5～5)
	attackPoint_ += -sizeRand+(-sizeRand*0.5f+2.5f); //ダメージ30+((10～-5)
	//小さい方がダメージ量がでかい
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
		charaBase_.color_, kFillModeSolid);
}
