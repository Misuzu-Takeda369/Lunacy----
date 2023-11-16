#include "PlayerIdolAnim.h"
#include "Function/Function.h"

void PlayerIdolAnim::Initialize()
{
	_texture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_Idol0.png");
	_texture[1] = Novice::LoadTexture("./Resources/images/AnimResources/player_Idol1.png");
	_texture[2] = Novice::LoadTexture("./Resources/images/AnimResources/player_Idol2.png");
	_lunaTexture[0]=Novice::LoadTexture("./Resources/images/AnimResources/player_luna_Idol0.png");
	_lunaTexture[1] = Novice::LoadTexture("./Resources/images/AnimResources/player_luna_Idol1.png");
	_lunaTexture[2] = Novice::LoadTexture("./Resources/images/AnimResources/player_luna_Idol2.png");
	_spriteSize = { 512.0f,512.0f };
	_spriteRadius = { _spriteSize.x*0.25f,_spriteSize.y *0.25f };
}

void PlayerIdolAnim::Update(Vector2 pos)
{
	_pos = pos;
	_timer++;
	if (_right) {
		_direction = 1.0f;
		_directionPos = 0;
	}
	else {
		_direction = -1.0f;
		_directionPos = (int)_spriteRadius.x;
	}

	if (_timer >= 7) {
		_frame = AnimationNum(_frame, 3);
		_timer = 0;
	}
}

void PlayerIdolAnim::Draw(UnitColor color)
{
	_color = color;
	if (_isLunatic) {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.y * 0.5f), (int)_pos.y - (int)(_spriteRadius.y * 0.5f), _lunaTexture[_frame], 0.25f * _direction, 0.25f, 0, WHITE);
	}
	else {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.y * 0.5f), (int)_pos.y - (int)(_spriteRadius.y * 0.5f), _texture[_frame], 0.25f * _direction, 0.25f, 0, WHITE);
	}
}

void PlayerIdolAnim::SetDirection(bool right)
{
	_right = right;
}

void PlayerIdolAnim::SetIsLunatic(MaindState state)
{
	_isLunatic = (bool)state;
}
