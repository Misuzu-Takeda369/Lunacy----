#pragma once
#include "Animation/Animation.h"
class PlayerRunAnim :public Animation
{
public:
	void Update(Vector2 pos)override;
	void Initialize()override;
	void Draw(UnitColor color)override;
	void SetDirection(bool right)override;
	bool GetActive() { return _isActive; }
	void PosReset();
protected:
	Vector2 _spriteSize;
	Vector2 _spriteSize2;
	Vector2 _spriteRadius;
	Vector2 _spriteRadius2;
	//TextureSet _texture;
	TexturePos _texPos;
	unsigned int _texture[4];
	unsigned int _lunaTexture[4];
	bool _right;

	int _frame = 0;

	Vector2 _pos;
};

