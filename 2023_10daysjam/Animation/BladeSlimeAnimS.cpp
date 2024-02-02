#include "BladeSlimeAnimS.h"
#include "Function/Function.h"
#include "ScreenSize.h"

void BladeSlimeAnimS::Initialize()
{
	
	lunaTex_ = Novice::LoadTexture("./Resources/images/AnimResources/bladesMind.png");
	lunaTexATK_ = Novice::LoadTexture("./Resources/images/AnimResources/bladesMindA.png");

	_timer = 0;
	atkFrame = 0;
	frame2 = 0;
	_spriteSize = { 1024.f * 0.25f,512.f * 0.25f };
	_spriteRadius = { _spriteSize.x * 0.5f,_spriteSize.y * 0.5f };
	_isActive = true;
	isAttacking_ = false;
	state_ = MOVE;

}

void BladeSlimeAnimS::Update(Vector2 pos)
{
	_pos = pos;
	_timer++;
	if (state_ == ATTACK) {
		if (_timer >= 7) {
			if (atkFrame == 4) {
				isAttacking_ = true;
			}
			if (!isAttacking_) {
				atkFrame = AnimationNum(atkFrame, 5);
				_timer = 0;
			}
		}
	}
	else {
		//frame = 0;
		atkFrame = 0;
		isAttacking_ = false;
		if (_timer >= 7) {
			frame2 = AnimationNum(frame2, 5);
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

void BladeSlimeAnimS::Draw(unsigned int color)
{
	
	if (((int)(_pos.x - _spriteRadius.x * _direction) <= kWindowWidth + _spriteSize.x) && ((int)(_pos.x - _spriteRadius.x * _direction) >= MimWindowWidth - _spriteSize.x)) {

		if (maindState_ == Lunatic) {
			if (state_ == ATTACK) {
				Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 256 * atkFrame, 0, 256, 128, lunaTexATK_,
					1 * _direction * 0.2f, 1, 0, WHITE);
			}
			else {
				Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 256 * frame2, 0, 256, 128, lunaTex_,
					1 * _direction * 0.2f, 1, 0, WHITE);
			}
		}
	}

	color;
}

void BladeSlimeAnimS::SetState(STATE state)
{
	state_ = state;
}

void BladeSlimeAnimS::SetDirection(bool right)
{
	_right = right;
}

void BladeSlimeAnimS::SetMaindState(const MaindState& state)
{
	maindState_ = state;
}
