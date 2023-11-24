#include "BladeSlimeAnim.h"
#include "Function/Function.h"

void BladeSlimeAnim::Initialize()
{
	texture_[0] = Novice::LoadTexture("./Resources/images/AnimResources/bladeSlime.png");
	texture_[1] = Novice::LoadTexture("./Resources/images/AnimResources/bladeSlime_Attack.png");
	rectTex_ = Novice::LoadTexture("./Resources/images/AnimResources/blades.png");
	rectTexATK_ = Novice::LoadTexture("./Resources/images/AnimResources/bladesA.png");
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

void BladeSlimeAnim::Update(Vector2 pos)
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
		frame = 0;
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

void BladeSlimeAnim::Draw(unsigned int color)
{
	if (maindState_ == Normal) {
		if (state_ == ATTACK) {
			Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 1024 * atkFrame, 0, 1024, 512, rectTexATK_,
				0.25f * _direction * 0.2f, 0.25f, 0, WHITE);
		}
		else {
			Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 1024 * frame2, 0, 1024, 512, rectTex_,
				0.25f * _direction * 0.2f, 0.25f, 0, WHITE);
		}
	}
	else {

		if (state_ == ATTACK) {
			Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 1024 * atkFrame, 0, 1024, 512, lunaTexATK_,
				0.25f * _direction * 0.2f, 0.25f, 0, WHITE);
		}
		else {
			Novice::DrawSpriteRect((int)(_pos.x - _spriteRadius.x * _direction), (int)(_pos.y - _spriteRadius.y), 1024 * frame2, 0, 1024, 512, lunaTex_,
				0.25f * _direction * 0.2f, 0.25f, 0, WHITE);
		}
		color;
	}
}

void BladeSlimeAnim::SetState(STATE state)
{
	state_ = state;
}

void BladeSlimeAnim::SetDirection(bool right)
{
	_right = right;
}

void BladeSlimeAnim::SetMaindState(const MaindState& state)
{
	maindState_ = state;
}
