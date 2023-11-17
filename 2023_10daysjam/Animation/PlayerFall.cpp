#include "PlayerFall.h"
#include "Function/Function.h"
void PlayerFall::Initialize()
{
	_texture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_fall.png");
	_lunaTexture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_luna_fall.png");
	_lunaTexture[1]= Novice::LoadTexture("./Resources/images/AnimResources/player_luna_fall2.png");
	_lunaTexture[2] = Novice::LoadTexture("./Resources/images/AnimResources/player_luna_fall3.png");


	_spriteSize = { 512.0f,512.0f };
	_spriteRadius = { _spriteSize.x * 0.25f,_spriteSize.y * 0.25f };
	_isActive = false;
}

void PlayerFall::Update(Vector2 pos)
{
	_pos = pos;
	//_timer++;
	if (_right) {
		_direction = 1.0f;
		_directionPos = 0;
	}
	else {
		_direction = -1.0f;
		_directionPos = (int)_spriteRadius.x;
	}

	if (_isLunatic) {
		
		
		if (!_isActive) {
			_timer++;
			if (_timer >= 5) {
				_frame = AnimationNum(_frame, maxFrame);
				_timer = 0;
				if (_frame == 2) {
					_isActive = true;
				}
			}
		}
		else {
			_frame = 2;
		}
	}
	else {
		_frame = 0;
	}
	
}

void PlayerFall::Draw(UnitColor color)
{
	_color = color;
	if (_isLunatic) {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.y * 0.5f), (int)_pos.y - (int)(_spriteRadius.y * 0.5f), _lunaTexture[_frame], 0.25f * _direction, 0.25f, 0, WHITE);
	}
	else {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.y * 0.5f), (int)_pos.y - (int)(_spriteRadius.y * 0.5f), _texture[_frame], 0.25f * _direction, 0.25f, 0, WHITE);
	}
}

void PlayerFall::SetDirection(bool right)
{
	_right = right;
}

void PlayerFall::SetIsLunatic(MaindState state)
{
	_isLunatic = (bool)state;
}

void PlayerFall::SetIsActive(bool flag)
{
	_isActive = flag;
	_frame = 0;
}
