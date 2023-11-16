#include "SpRecoverItem.h"

void SpRecoverItem::Initialize(Vector2& pos)
{
	//多分敵のドロップか時間経過か
	charaBase_.pos_ = pos;
	charaBase_.radius_ = 32.0f;
	//画像サイズ
	sizeX_ = 32; sizeY_ = 32;
	image_= Novice::LoadTexture("./Resources/images/Item/Item_2.png");

	//実際に回復する量
	recoverSp_ = recoveryAmount_;
	//ラインが下がる量
	downLineLunatic_ = downLineLunaticAmount_;
}

void SpRecoverItem::Update()
{
	//アイテムが消える(時間経過)
	
	--deathTimer_;
	if (deathTimer_ <= 0) {
		isDead_ = true;
	}
	

}

void SpRecoverItem::Draw()
{
	//Novice::DrawEllipse(int(charaBase_.pos_.x), int(charaBase_.pos_.y), int(charaBase_.radius_), int(charaBase_.radius_),0.0f,WHITE,kFillModeSolid);
	Novice::DrawSprite(int(charaBase_.pos_.x), int(charaBase_.pos_.y), image_,1.0f/8.0f, 1.0f / 8.0f,0.0f,WHITE);
	//Novice::DrawEllipse(100,600, 100, 100, 0.0f, RED, kFillModeSolid);
}
