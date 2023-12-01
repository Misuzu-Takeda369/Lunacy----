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
	void SetMaindState(const MaindState& state);//敵の攻撃タイプ まだ通常しかない
private:
	/*static const int maxFrame = 2;
	unsigned int texture_[maxFrame];*/
	unsigned int rectTex_;
	unsigned int rectTexATK_;
	/*unsigned int lunaTex_;
	unsigned int lunaTexATK_;*/
	//int frame = 0;
	int frame2 = 0;
	int atkFrame = 0;
	bool isAttacking_ = false;
	STATE state_ = STATE::IDOL;
	bool _right;
	MaindState maindState_ = MaindState::Normal;
};

