#pragma once
#include "Animation.h"
class PlayerAttackAnim1 :
    public Animation
{
public:
	void Initialize()override;
	void Update(Vector2 pos)override;
	void Draw(UnitColor color)override;
	void SetDirection(bool right)override;
	void SetIsLunatic(MaindState state)override;
	void SetActive(bool flag)override;

private:
	unsigned static const int _maxFrame = 1;
	TexturePos _texPos;
	unsigned int _texture[_maxFrame];
	unsigned static const int _maxLunaFrame = 2;
	unsigned int _lunaTexture[_maxLunaFrame];
	unsigned int _nowTexture;
	Vector2 _pos;
	int _frame = 0;
	bool _right;
	int _lunaFrame = 0;
	bool _lunaAnimFrameFlag = false;
};

