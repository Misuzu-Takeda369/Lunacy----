#pragma once
#include "Animation.h"
class PlayerAttack2Anim :
    public Animation
{
public:
	void Initialize()override;
	void Update(Vector2 pos)override;
	void Draw(UnitColor color)override;
	void SetDirection(bool right)override;
	void SetIsLunatic(MaindState state)override;

private:
	TexturePos _texPos;
	unsigned int _texture[1];
	Vector2 _pos;
	unsigned int _lunaTexture[1];

};

