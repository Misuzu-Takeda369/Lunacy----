#pragma once
#include "Animation.h"
class Enemy1Anim:public Animation
{
public:
	void Initialize()override;
	void Update(Vector2 pos)override;
	void Draw(unsigned int color);
private:
	static const int maxFrame = 4;
	unsigned int texture_[maxFrame];
	int frame = 0;

};

