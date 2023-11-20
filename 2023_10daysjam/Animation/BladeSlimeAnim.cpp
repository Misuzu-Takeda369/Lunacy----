#include "BladeSlimeAnim.h"

void BladeSlimeAnim::Initialize()
{
	texture_[0] = Novice::LoadTexture("./Resources/images/AnimResources/bladeSlime.png");
	texture_[1] = Novice::LoadTexture("./Resources/images/AnimResources/bladeSlime_Attack.png");
	
	_timer = 0;
	_spriteSize = { 1024.f * 0.25f,512.f * 0.25f };
	_spriteRadius = { _spriteSize.x * 0.5f,_spriteSize.y * 0.5f };
	_isActive = true;

}

void BladeSlimeAnim::Update(Vector2 pos)
{
	_pos = pos;
	_timer++;
	if (state_ == ATTACK) {
		frame = 1;
	}
	else {
		frame = 0;
	}
	if (_right) {
		_direction = 1.0f;
	}
	else {
		_direction = -1.0f;
	}

}

void BladeSlimeAnim::Draw(unsigned int color)
{
	Novice::DrawSprite((int)(_pos.x - _spriteRadius.x*_direction), (int)(_pos.y - _spriteRadius.y), texture_[frame], 0.25f*_direction, 0.25f, 0, color);
}

void BladeSlimeAnim::SetState(STATE state)
{
	state_ = state;
}

void BladeSlimeAnim::SetDirection(bool right)
{
	_right = right;
}