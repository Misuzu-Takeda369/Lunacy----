#pragma once
#include "Animation/Animation.h"
#include "Function/UtilityStruct.h"
class BladeSlimeAnim:public Animation
{
public:
	void Initialize()override;
	void Update(Vector2 pos)override;
	void Draw(unsigned int color);
	void SetState(STATE state);
	void SetDirection(bool right)override;
private:
	static const int maxFrame = 2;
	unsigned int texture_[maxFrame];
	int frame = 0;
	STATE state_ = STATE::IDOL;
	bool _right;
};

