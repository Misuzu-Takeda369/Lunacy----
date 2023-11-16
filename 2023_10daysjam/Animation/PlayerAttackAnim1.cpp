#include "PlayerAttackAnim1.h"
#include "Function/Function.h"

void PlayerAttackAnim1::Initialize()
{
	_texture[0] = Novice::LoadTexture("./Resources/images/AnimResources/player_attack.png");
	_lunaTexture[0]= Novice::LoadTexture("./Resources/images/AnimResources/player_attack_luna1.png");
	_lunaTexture[1] = Novice::LoadTexture("./Resources/images/AnimResources/player_attack_luna2.png");
	_spriteSize = { 1024,512 };
	_spriteRadius = { 512,256};
	_lunaAnimFrameFlag = false;
	_nowTexture = _texture[0];
}

void PlayerAttackAnim1::Update(Vector2 pos)
{
	_pos = pos;
	if (_right) {
		_direction = 1.0f;
		_directionPos = (int)(_spriteRadius.x * -0.25f)+(int)(_spriteRadius.y*0.25f);
	}
	else {
		_direction = -1.0f;
		_directionPos = (int)(_spriteRadius.x*0.5f) - (int)(_spriteRadius.y * 0.25f);
	}
	_timer++;
	if (_timer >= 7) {
		_frame = AnimationNum(_frame, _maxFrame);
		_timer = 0;
	}
	if (_isActive) {
		if (_isLunatic) {
			if (!_lunaAnimFrameFlag) {
				_lunaFrame++;
				_nowTexture = _lunaTexture[0];
				if (_lunaFrame >= 3) {
					_lunaAnimFrameFlag = true;
					_lunaFrame = 0;
				}
			}
			else {
				_nowTexture = _lunaTexture[1];
			}
		}
		else {
			_nowTexture = _texture[0];
		}
	}
	else {
		_lunaAnimFrameFlag = false;
		_lunaFrame = 0;
	}
}

void PlayerAttackAnim1::Draw(UnitColor color)
{
	_color = color;
	int a =int( 512 *0.5f * 0.25f);
	Novice::DrawSprite((int)((_pos.x)+_directionPos)-a, (int)_pos.y-a, _nowTexture, 0.25f*_direction, 0.25f, 0, WHITE);

}

void PlayerAttackAnim1::SetDirection(bool right)
{
	_right = right;
}

void PlayerAttackAnim1::SetIsLunatic(MaindState state)
{
	_isLunatic = (bool)state;
}

void PlayerAttackAnim1::SetActive(bool flag)
{
	_isActive = flag;
}
