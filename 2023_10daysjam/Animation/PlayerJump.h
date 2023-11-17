#pragma once
#include "Animation.h"
class PlayerJump :
    public Animation
{
	//落下用
public:
	void Initialize()override;
	void Update(Vector2 pos)override;
	void Draw(UnitColor color)override;
	void SetDirection(bool right)override;
	void SetIsLunatic(MaindState state)override;
	void SetIsActive(bool flag);
private:
	TexturePos _texPos;
	static unsigned const int maxFrame = 2;
	unsigned int _texture[maxFrame];
	unsigned int _nowTexture;
	unsigned int _lunaNow;
	Vector2 _pos;
	bool _right;
	bool _isActive = false;
	bool _airFlag = false;

	unsigned int _lunaTexture[maxFrame];

	int _frame = 0;
};

