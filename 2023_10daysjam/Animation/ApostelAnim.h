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
	void SetColorRGBA(int R, int G, int B, int A);
	void SetMaskBreak(bool flag);
private:
	void LoadTexture();
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
	unsigned int color_ = WHITE;
	bool maskBreak_ = false;

	//スプライト用
	struct CharaParts
	{
		unsigned int hair_back;
		unsigned int hair_front;
		unsigned int hair_side;
		unsigned int eye;
		unsigned int mask;
		unsigned int mask_eye;
		unsigned int mouth;
		unsigned int head;
		unsigned int body;
	};
	CharaParts sprite_;
};

