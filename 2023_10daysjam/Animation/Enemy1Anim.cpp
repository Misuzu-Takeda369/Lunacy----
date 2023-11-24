#include "Enemy1Anim.h"
#include "Function/Function.h"
#include <Novice.h>

void Enemy1Anim::Initialize()
{
	texture_[0] = Novice::LoadTexture("./Resources/images/AnimResources/enemy_1_1.png");
	texture_[1] = Novice::LoadTexture("./Resources/images/AnimResources/enemy_1_2.png");
	texture_[2] = Novice::LoadTexture("./Resources/images/AnimResources/enemy_1_3.png");
	texture_[3] = Novice::LoadTexture("./Resources/images/AnimResources/enemy_1_2.png");
	_timer = 0;
	_spriteSize = { 512.f * 0.25f,512.f * 0.25f };
	_spriteRadius = { _spriteSize.x * 0.5f,_spriteSize.y * 0.5f };
	_isActive = true;
	
}

void Enemy1Anim::Update(Vector2 pos)
{
	_pos = pos;
	_timer++;
	if (_timer >= 7) {
		frame=AnimationNum(frame, maxFrame);
		_timer = 0;
	}
}

void Enemy1Anim::Draw(unsigned int color)
{
	Novice::DrawSprite((int)(_pos.x-_spriteRadius.x), (int)(_pos.y-_spriteRadius.y), texture_[frame], 0.25f, 0.25f, 0, color);


}
