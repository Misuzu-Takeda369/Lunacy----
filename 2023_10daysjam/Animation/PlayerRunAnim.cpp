#include "PlayerRunAnim.h"
#include "Function/Function.h"

void PlayerRunAnim::Initialize()
{
	_texture[0] = Novice::LoadTexture("./Resources/images/AnimResources/w1.png");
	_texture[1] = Novice::LoadTexture("./Resources/images/AnimResources/w4.png");
	_texture[2] = Novice::LoadTexture("./Resources/images/AnimResources/w2.png");
	_texture[3] = Novice::LoadTexture("./Resources/images/AnimResources/w3.png");
	_lunaTexture[0]= Novice::LoadTexture("./Resources/images/AnimResources/w1_luna.png");
	_lunaTexture[1] = Novice::LoadTexture("./Resources/images/AnimResources/w4_luna.png");
	_lunaTexture[2] = Novice::LoadTexture("./Resources/images/AnimResources/w2_luna.png");
	_lunaTexture[3] = Novice::LoadTexture("./Resources/images/AnimResources/w3_luna.png");
	_spriteSize = { 512.0f,512.0f };
	_spriteRadius = { _spriteSize.x * 0.25f,_spriteSize.y  * 0.25f };
	_isLunatic = false;
}

void PlayerRunAnim::Draw(UnitColor color)
{
	_color = color;
	if (_isLunatic) {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.x * 0.5f), (int)_pos.y - (int)(_spriteRadius.x * 0.5f), _lunaTexture[_frame], 0.25f * _direction, 0.25f, 0, _color.color);
	}
	else
	{
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.x * 0.5f), (int)_pos.y - (int)(_spriteRadius.x * 0.5f), _texture[_frame], 0.25f * _direction, 0.25f, 0, _color.color);
	}
}

void PlayerRunAnim::SetDirection(bool right)
{
	_right = right;
}

void PlayerRunAnim::PosReset()
{
	_frame = 0;
}

void PlayerRunAnim::Update(Vector2 pos)
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
		_frame = AnimationNum(_frame, 4);
		_timer = 0;
	}

}