#pragma once
#include "Animation.h"
class ApostelAnim :public Animation
{
public:
	void Initialize()override;
	void Update(Vector2 pos)override;
	void Draw(unsigned int color);
	void SetState(STATE state);
	void SetDirection(bool right)override;
private:
	static const int maxFrame = 1;
	unsigned int rectTex_;
	unsigned int rectTexATK_;//準備してない
	int frame = 0;
	int frame2 = 0;
	int atkFrame = 0;
	bool isAttacking_ = false;
	STATE state_ = STATE::IDOL;
	bool _right;
	MaindState maindState_ = MaindState::Normal;
};

