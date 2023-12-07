#include "ApostelAnim.h"

void ApostelAnim::Initialize()
{
	rectTex_ = Novice::LoadTexture("./Resources/images/AnimResources/apostel_test.png");
	//rectTexATK_ = Novice::LoadTexture("./Resources/images/AnimResources/flyEye.png");

	_timer = 0;
	atkFrame = 0;
	frame2 = 0;
	_spriteSize = { 512.f * 0.25f,512.f * 0.25f };
	_spriteRadius = { _spriteSize.x * 0.5f,_spriteSize.y * 0.5f };
	_isActive = true;
	isAttacking_ = false;
	state_ = IDOL;
}

void ApostelAnim::Update(Vector2 pos)
{
	_pos = pos;
	if (_right) {
		_direction = -1.0f;
	}
	else {
		_direction = 1.0f;
	}
}

void ApostelAnim::Draw(unsigned int color)
{
	color;
	Novice::DrawSprite((int)(_pos.x - _spriteRadius.x * _direction), (int)_pos.y - (int)(_spriteRadius.x ), rectTex_, 0.25f * _direction, 0.25f, 0, WHITE);
}

void ApostelAnim::SetState(STATE state)
{
	state_ = state;
}

void ApostelAnim::SetDirection(bool right)
{
	_right = right;
}
