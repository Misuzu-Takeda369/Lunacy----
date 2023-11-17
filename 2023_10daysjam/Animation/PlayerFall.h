#pragma once
#include "Animation.h"
class PlayerFall :
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
	static unsigned const int maxFrame = 3;
	unsigned int _texture[maxFrame];
	Vector2 _pos;
	bool _right;
	bool _isActive;

	unsigned int _lunaTexture[maxFrame];

	int _frame = 0;
};

