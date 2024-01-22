#include "PlayerAttack2Anim.h"

void PlayerAttack2Anim::Initialize()
{
	_texture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_magic.png");
	_lunaTexture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_magic_luna.png");
	_spriteSize = { 512,512 };
	_spriteRadius = { _spriteSize.x * 0.5f, };

	_midleTexture = Novice::LoadTexture("./Resources/images/AnimResources/PlayerMagicmidleB.png");
	_midleDicrection_ = 0;
}

void PlayerAttack2Anim::Update(Vector2 pos)
{
	_pos = pos;
	if (_isDirectionRight) {
		_direction = 1.0f;
		_directionPos = 0;
		_midleDicrection_ = 0;
	}
	else {
		_direction = -1.0f;
		_directionPos = (int)(_spriteRadius.x * 0.5f);
		_midleDicrection_ = _midleTexPosX *2;
	}
}

void PlayerAttack2Anim::Draw(UnitColor color)
{
	_color = color;
	if (_isLunatic) {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.x * 0.25f), (int)_pos.y - (int)(_spriteRadius.x * 0.25f), _lunaTexture[0], 0.25f * _direction, 0.25f, 0, WHITE);
	}
	else {
		Novice::DrawSprite((int)_pos.x + _directionPos - (int)(_spriteRadius.x * 0.25f), (int)_pos.y - (int)(_spriteRadius.x * 0.25f), _texture[0], 0.25f * _direction, 0.25f, 0, WHITE);
	}

	Novice::DrawSprite((int)_pos.x + _midleTexPosX- _midleDicrection_, (int)_pos.y - _midleTexPosY, _midleTexture,1.0f * _direction,1.0f ,0.0f,WHITE);
}

void PlayerAttack2Anim::SetDirection(bool right)
{
	_isDirectionRight = right;
}

void PlayerAttack2Anim::SetIsLunatic(MaindState state)
{
	_isLunatic = (bool)state;
}
