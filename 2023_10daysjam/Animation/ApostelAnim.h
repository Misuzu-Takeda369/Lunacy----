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
	void SetNowPhase(int num);
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
	int nowPhase_;

	//スプライト用
	struct CharaParts
	{
		unsigned int hair_back;
		unsigned int hair_front;
		unsigned int hair_side;
		unsigned int eye;
		unsigned int mask;
		unsigned int mask_eye;
		unsigned int mask_eye_third;
		unsigned int mouth;
		unsigned int mouth_third;
		unsigned int mouth_dead;
		unsigned int head;
		unsigned int body;
		unsigned int halfmask;
		unsigned int halfmask_third;
		unsigned int eye_second;
		unsigned int body_second;
		unsigned int body_third;
		unsigned int armR_third;
		unsigned int armL_third;
	};
	unsigned int body_back;
	int body_backCount = 0;
	int body_backFrame = 0;
	float thirdRotateArm_ = 0;
	float thirdRotateArmSpeed_ = 0.05f;
	Vector2 armLPos; Vector2 armRPos;
	CharaParts sprite_;
};

