#pragma once
#include "Animation/AnimationStruct.h"
#include <Novice.h>
#include "Function/UtilityStruct.h"
#include "CharaBase.h"
class Animation
{
public:
	virtual void Initialize();
	virtual void Update(Vector2 pos);
	virtual void Draw(UnitColor color);
	virtual void SetActive(bool flag);
	virtual void SetDirection(bool right);
	virtual void SetIsLunatic(MaindState state );
protected:
	Vector2 _spriteSize;
	Vector2 _spriteRadius;
	Vector2 _pos;
	TextureSet _texture;
	TexturePos _texPos;
	bool _isDirectionRight;
	float _direction = 1.0f;
	int _directionPos;

	bool _isActive = false;
	int _timer = 0;
	UnitColor _color=defaultColor;
	bool _isLunatic;

};


