#include "PlayerAttackAnim.h"
#include <Function/Easing.h>


void PlayerAttackAnim::Initialize()
{
	_texture.head = Novice::LoadTexture("../Resources/images/AnimResources/player_head.png");
	_texture.body = Novice::LoadTexture("./Resources/images/AnimResources/player_body.png");
	_texture.leftArm = Novice::LoadTexture("./Resources/images/AnimResources/player_attack_arm1.png");
	_texture.weapon = Novice::LoadTexture("./Resources/images/AnimResources/player_weapon.png");
	_texture.sprite = Novice::LoadTexture("./Resources/images/AnimResources/player_attack_arm2.png");
	_texture.sprite1 = Novice::LoadTexture("./Resources/images/AnimResources/player_attack_head1.png");
	_spriteSize = { 256,256 };//自機
	_spriteSize2 = { 512,256 };//武器
	_spriteRadius.x = _spriteSize.x * 0.5f;
	_spriteRadius.y = _spriteSize.y * 0.5f;
	_spriteRadius2.x = _spriteSize2.x * 0.5f;
	_spriteRadius2.y = _spriteSize2.y * 0.5f;
}

void PlayerAttackAnim::Draw()
{
	Novice::DrawSprite((int)_pos.x-(int)_texPos.rightArm.x+_directionPos, (int)_pos.y-(int)_texPos.rightArm.y, _texture.sprite, _rate, _baseRate, 0, WHITE);
	Novice::DrawSprite((int)_pos.x-(int)_texPos.body.x+_directionPos, (int)_pos.y-(int)_texPos.body.y, _texture.body, _rate, _baseRate, 0, WHITE);
	if (!_attack) {
		Novice::DrawSprite((int)_pos.x - (int)_texPos.head.x + _directionPos, (int)_pos.y - (int)_texPos.head.y, _texture.head, _rate, _baseRate, 0, WHITE);
		Novice::DrawSprite((int)_pos.x - (int)_texPos.weapon.x + _directionPos, (int)_pos.y - (int)_texPos.weapon.y, _texture.weapon, _rate, _baseRate, _weaponRotate, WHITE);
		Novice::DrawSprite((int)_pos.x - (int)_texPos.leftArm.x + _directionPos, (int)_pos.y - (int)_texPos.leftArm.y, _texture.leftArm, _rate, _baseRate, 0, WHITE);
	}
	else {	
		Novice::DrawSprite((int)_pos.x - (int)_texPos.head.x + _directionPos, (int)_pos.y - (int)_texPos.head.y, _texture.sprite1, _rate, _baseRate, 0, WHITE);
		Novice::DrawSprite((int)_pos.x - (int)_texPos.weapon.x + _directionPos, (int)_pos.y - (int)_texPos.weapon.y, _texture.weapon, _rate, _baseRate, _weaponRotate, WHITE);
		Novice::DrawSprite((int)_pos.x - (int)_texPos.leftArm.x + _directionPos, (int)_pos.y - (int)_texPos.leftArm.y, _texture.sprite, _rate, _baseRate, 0, WHITE);
	}
	
}

void PlayerAttackAnim::SetActive(bool flag)
{
	isActive = flag;
	_attack = false;
	_timer = 0;
}

void PlayerAttackAnim::SetDirection(bool right)
{
	_right = right;
}

void PlayerAttackAnim::PosReset()
{
	_texPos.body.x = 0 - _spriteRadius.x * 0.5f;
	_texPos.body.y = 0 - _spriteRadius.y * 0.5f;
	_texPos.head.x = 0 - _spriteRadius.x * 0.5f;
	_texPos.head.y = _texPos.body.y + _spriteRadius.y*0.5f * 0.95f;
	_texPos.weapon.x = 0 - _spriteRadius2.x * 0.25f;
	_texPos.weapon.y = 0 - _spriteRadius2.y * 0.5f;
	_texPos.leftArm.x = 0 - _spriteRadius.x * 0.5f;
	_texPos.leftArm.y = 0 - _spriteRadius.y * 0.5f;
	_texPos.rightArm.x = 0 - _spriteRadius.x * 0.5f;
	_texPos.rightArm.y = 0 - _spriteRadius.y *0.5f;
	_weaponRotate = 0.0f;
	theta = 0;
}

void PlayerAttackAnim::Update(Vector2 pos)
{
	_pos = pos;
	if (_right) {
		_direction = 1.0f;
		_directionPos = 0;
	}
	else {
		_direction = -1.0f;
		_directionPos = (int) _spriteRadius.x;
	}
	_rate = _baseRate * _direction;
	if (!isActive) {
		PosReset();
	}
	//Spear();
	Slash();
}

void PlayerAttackAnim::Spear()
{
	if (isActive) {
		_timer++;
		
		if (_timer < 5) {
			_texPos.leftArm.x += 0.5f * _direction;
			_texPos.weapon.x += 1.0f * _direction;
			_texPos.head.y -= 0.5f;
		}
		else if (_timer < 10) {
			if (_timer < 7) {
				_texPos.head.y += 0.5f;
			}
			_attack = true;
			_texPos.weapon.x -= 10.0f * _direction;
			_texPos.leftArm.x -= 3.0f * _direction;
		}
		else if (_timer < 13) {
			_texPos.leftArm.x += 2.0f;
			_texPos.weapon.x += 2.0f * _direction;
		}
		else {
			isActive = false;
			_attack = false;
			PosReset();
		}


	}
}

void PlayerAttackAnim::Slash()
{
	if (isActive) {
		_timer++;
		if (theta <= 1.0f) {
			theta += 0.01f;
		}
		_weaponRotate = Easeing(theta,EASE::___EaseInOutQuint);

		//CircumferentialMovement(_texPos.weapon, _weaponRotate);
		if (_timer < 2) {
			//_weaponRotate -= DegreeToRadian(60) * _direction;
		}
		else if (_timer < 8) {
			_attack = true;
			//_weaponRotate += DegreeToRadian(10) * _direction;
		}
		else if (_timer < 15) {

		}
		else {
			//isActive = false;
			_attack = false;
			//PosReset();
		}


	}

}


