#include "FlyEye.h"
#include "Function/Function.h"

void FlyEye::Initialize()
{
	
	rectTex_ = Novice::LoadTexture("./Resources/images/AnimResources/flyEyemini.png");
	rectTexATK_ = Novice::LoadTexture("./Resources/images/AnimResources/flyEyemini.png");

	_timer = 0;
	atkFrame = 0;
	frame2 = 0;
	_spriteSize = { 512.f * 0.25f,512.f * 0.25f };
	_spriteRadius = { _spriteSize.x * 0.5f,_spriteSize.y * 0.5f };
	_isActive = true;
	isAttacking_ = false;
	state_ = MOVE;

}

void FlyEye::Update(Vector2 pos)
{
	_pos = pos;
	_timer++;
	if (state_ == ATTACK) {
		if (_timer >= 7) {
			if (atkFrame == 5) {
				isAttacking_ = true;
			}
			if (!isAttacking_) {
				atkFrame = AnimationNum(atkFrame, 6);
				_timer = 0;
			}
		}
	}
	else {
		frame = 0;
		atkFrame = 0;
		isAttacking_ = false;
		if (_timer >= 7) {
			frame2 = AnimationNum(frame2, 6);
			_timer = 0;
		}
	}
	if (_right) {
		_direction = 1.0f;
	}
	else {
		_direction = -1.0f;
	}

}

void FlyEye::Draw(unsigned int color)
{
	if (state_ == ATTACK) {
	/*	Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 512 * atkFrame, 0, 512, 512, rectTexATK_,
			0.25f * _direction * 0.166f, 0.25f, 0, WHITE);*/
		Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 128 * atkFrame, 0, 128, 128, rectTexATK_,
			1.0f * _direction * 0.166f, 1.0f, 0, WHITE);

	}
	else {
		/*Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 512 * frame2, 0, 512, 512, rectTex_,
			0.25f * _direction * 0.166f, 0.25f, 0, WHITE);*/
		Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 128 * frame2, 0, 128, 128, rectTex_,
			1.0f * _direction * 0.166f, 1.0f, 0, WHITE);
	}

	color;
}
void FlyEye::SetState(STATE state)
{
	state_ = state;
}

void FlyEye::SetDirection(bool right)
{
	_right = right;
}