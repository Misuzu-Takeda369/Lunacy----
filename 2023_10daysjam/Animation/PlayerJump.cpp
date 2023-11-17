#include "PlayerJump.h"
#include "Function/Function.h"
void PlayerJump::Initialize()
{
	_texture[1] = Novice::LoadTexture("./Resources/images/AnimResources/player_jump_air.png");
	_texture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_jump_air.png");

	_lunaTexture[1] = Novice::LoadTexture("./Resources/images/AnimResources/player_luna_jump_air.png");
	_lunaTexture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_luna_jump_air.png");

	_spriteSize = { 512.0f,512.0f };
	_spriteRadius = { _spriteSize.x * 0.25f,_spriteSize.y * 0.25f };
	_frame = 0;
	_isActive = false;
}

void PlayerJump::Update(Vector2 pos)
{
	_pos = pos;
	if (_right) {
		_direction = 1.0f;
		_directionPos = 0;
	}
	else {
		_direction = -1.0f;
		_directionPos = (int)_spriteRadius.x;
	}

	if (_isActive) {
		if (!_airFlag) {
			_timer++;
			_nowTexture = _texture[0];
			_lunaNow = _lunaTexture[0];
			if (_timer >= 3) {
				_airFlag = true;
				_timer = 0;
			}
		}
		else {
			_nowTexture = _texture[1];
			_lunaNow = _lunaTexture[1];
		}
	}
	else {
		_airFlag = false;
		_timer = 0;
	}

	/*
	if (_timer >= 5) {
		_isActive = true;
	}
	
	if (!_isActive) {
		_nowTexture = _texture[0];
 		_lunaNow = _lunaTexture[0];
	}
	else {
		_nowTexture = _texture[1];
		_lunaNow = _lunaTexture[1];
	}*/
	
}

void PlayerJump::Draw(UnitColor color)
{
	_color = color;
	if (_isLunatic) {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.y * 0.5f), (int)_pos.y - (int)(_spriteRadius.y * 0.5f), _lunaNow, 0.25f * _direction, 0.25f, 0, WHITE);
	}
	else {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.y * 0.5f), (int)_pos.y - (int)(_spriteRadius.y * 0.5f), _nowTexture, 0.25f * _direction, 0.25f, 0, WHITE);
	}
}

void PlayerJump::SetDirection(bool right)
{
	_right = right;
}

void PlayerJump::SetIsLunatic(MaindState state)
{
	_isLunatic = (bool)state;
}

void PlayerJump::SetIsActive(bool flag)
{
	_isActive = flag;
}
