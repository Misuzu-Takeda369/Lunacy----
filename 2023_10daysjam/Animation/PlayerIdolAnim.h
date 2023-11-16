#pragma once
#include "Animation/Animation.h"
class PlayerIdolAnim :public Animation
{
public:
	void Initialize()override;
	void Update(Vector2 pos)override;
	void Draw(UnitColor color)override;
	void SetDirection(bool right)override;
	void SetIsLunatic(MaindState state)override;

private:
	TexturePos _texPos;
	unsigned int _texture[3];
	Vector2 _pos;
	bool _right;

	unsigned int _lunaTexture[3];
	
	int _frame = 0;
};

