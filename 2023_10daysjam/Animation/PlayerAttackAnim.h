#pragma once
#include "Animation/Animation.h"
#include "Function/Function.h"
//没
class PlayerAttackAnim :public Animation
{
public:
	void Update(Vector2 pos)override;
	void Initialize()override;
	void Draw();
	void SetActive(bool flag)override;
	void SetDirection(bool right)override;
	bool GetActive() { return isActive; }
	void PosReset();
protected:
	void Spear();
	void Slash();
	Vector2 _spriteSize;
	Vector2 _spriteSize2;
	Vector2 _spriteRadius;
	Vector2 _spriteRadius2;
	TextureSet _texture;
	TexturePos _texPos;

	Vector2 _pos;

	bool isActive = false;
	int _timer = 0;
	bool _attack = false;
	float _rate = 0.5f;
	const float _baseRate = 0.25f;
	bool _right = true;
	float _direction = 1.0f;
	int _directionPos = 0;
	float _weaponRotate = 0;
	float theta=0;

};