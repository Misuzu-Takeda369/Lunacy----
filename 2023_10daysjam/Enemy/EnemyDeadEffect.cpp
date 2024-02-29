#include "EnemyDeadEffect.h"

void EnemyDeadEffect::Initialize(Vector2& pos)
{
	charaBase_.pos_ = { pos };
	charaBase_.Color_ = {255,0,0,0,WHITE};
	image_ = Novice::LoadTexture("./Resources/images/AnimResources/bladesDed.png");
}

void EnemyDeadEffect::Update()
{
	++deadTimer_;
	if (deadTimer_ >= KdeadTimer_) {
		isDead_ = true;
	}


	if (deadTimer_ >= KdeadTimer_/2) {
		charaBase_.Color_.color -= 0x0000010;
	}
	if (deadTimer_ >= (KdeadTimer_ / 2)+(KdeadTimer_ / 4)) {
		_scaleX += 0.01f;
		_scaleY += 0.01f;
	}
	
	
}

void EnemyDeadEffect::Draw()
{
	
	//Novice::DrawSprite(int(charaBase_.pos_.x), int(charaBase_.pos_.y), image_, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(int(charaBase_.pos_.x)- _spriteRadius.x_, int(charaBase_.pos_.y) - _spriteRadius.y_, image_, _scaleX, _scaleY, 0.0f, charaBase_.Color_.color);
}
