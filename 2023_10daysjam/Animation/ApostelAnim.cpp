#include "ApostelAnim.h"
#include "Function/Function.h"

void ApostelAnim::Initialize()
{
	rectTex_ = Novice::LoadTexture("./Resources/images/AnimResources/apostel_test.png");
	//rectTexATK_ = Novice::LoadTexture("./Resources/images/AnimResources/flyEye.png");
	LoadTexture();
	_timer = 0;
	atkFrame = 0;
	frame2 = 0;
	_spriteSize = { 512.f * 0.25f,512.f * 0.25f };
	_spriteRadius = { _spriteSize.x * 0.5f,_spriteSize.y * 0.5f };
	_isActive = true;
	isAttacking_ = false;
	state_ = IDOL;
	color_ = WHITE;
	maskBreak_ = false;
	body_backCount = 0;
	body_backFrame = 0;
	thirdRotateArm_ = 0;
	thirdRotateArmSpeed_ = 0.005f;
}

void ApostelAnim::Update(Vector2 pos)
{
	_pos = pos;
	if (_right) {
		_direction = -1.0f;
	}
	else {
		_direction = 1.0f;
	}
	body_backCount++;
	if (body_backCount >= 7) {
		body_backCount = 0;
		body_backFrame = AnimationNum(body_backFrame, 3);
	}
	if (nowPhase_ == 3) {
		thirdRotateArm_ += thirdRotateArmSpeed_;
		if (thirdRotateArm_ > 0.5f || thirdRotateArm_ < -0.5f) {
			thirdRotateArmSpeed_ = -thirdRotateArmSpeed_;
		}
		
	}
}

void ApostelAnim::Draw(unsigned int color)
{
	color;
	//Novice::DrawSprite((int)(_pos.x - _spriteRadius.x * _direction), (int)_pos.y - (int)(_spriteRadius.x ), rectTex_, 0.25f * _direction, 0.25f, 0, color_);
	//body back
	DrawRotateScaleSprite(_pos, { 256.f,256.f }, 256 * body_backFrame, 0, body_back, color_, { 0.25f * _direction,0.25f }, 0);
	
	// hair back
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.hair_back, color_, { 0.125f * _direction,0.125f }, 0);
	
	// head
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.head, color_, { 0.125f * _direction,0.125f }, 0);
	
	// eye
	if (nowPhase_ == 3||nowPhase_==0) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.eye, color_, { 0.125f * _direction,0.125f }, 0);
	}
	else if (nowPhase_ == 2) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.eye_second, color_, { 0.125f * _direction,0.125f }, 0);
	}
	//mouth
	if (nowPhase_ == 3) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mouth_third, color_, { 0.125f * _direction,0.125f }, 0);
	}
	else if (nowPhase_ == 0) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mouth_dead, color_, { 0.125f * _direction,0.125f }, 0);
	}
	else {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mouth, color_, { 0.125f * _direction,0.125f }, 0);
	}

	// hair side
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.hair_side, color_, { 0.125f * _direction,0.125f }, 0);
	
	// mask
	if (!maskBreak_) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mask, color_, { 0.125f * _direction,0.125f }, 0);
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mask_eye, color_, { 0.125f * _direction,0.125f }, 0);
	}
	else {
		if (nowPhase_ == 2) {
			DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.halfmask, color_, { 0.125f * _direction,0.125f }, 0);
		}
		else {
			DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.halfmask_third, color_, { 0.125f * _direction,0.125f }, 0);
			DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mask_eye_third, color_, { 0.125f * _direction,0.125f }, 0);
		}
	}
	
	// hair front
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.hair_front, color_, { 0.125f * _direction,0.125f }, 0);
	
	// body
	if (nowPhase_ == 2) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.body_second, color_, { 0.125f * _direction,0.125f }, 0);
	}
	else if (nowPhase_ == 3) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.body_third, color_, { 0.125f * _direction,0.125f }, 0);
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.armR_third, color_, { 0.125f * _direction,0.125f }, thirdRotateArm_*_direction);
		DrawRotateScaleSprite(_pos, { 550.f,512.f }, 0, 0, sprite_.armL_third, color_, { 0.125f * _direction,0.125f }, -thirdRotateArm_*_direction);
	}
	else {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.body, color_, { 0.125f * _direction,0.125f }, 0);
	}
}

void ApostelAnim::SetState(STATE state)
{
	state_ = state;
}

void ApostelAnim::SetDirection(bool right)
{
	_right = right;
}

void ApostelAnim::SetColorRGBA(int R, int G, int B, int A)
{
	color_ = GetColorValue(R, G, B, A);
}

void ApostelAnim::SetMaskBreak(bool flag)
{
	maskBreak_ = flag;
}

void ApostelAnim::SetNowPhase(int num)
{
	nowPhase_ = num;
}

void ApostelAnim::LoadTexture()
{
	sprite_.body = Novice::LoadTexture("./Resources/images/AnimResources/apos/body.png");
	sprite_.eye = Novice::LoadTexture("./Resources/images/AnimResources/apos/eye.png");
	sprite_.hair_back= Novice::LoadTexture("./Resources/images/AnimResources/apos/hair_back.png");
	sprite_.hair_side= Novice::LoadTexture("./Resources/images/AnimResources/apos/hair_side.png");
	sprite_.hair_front= Novice::LoadTexture("./Resources/images/AnimResources/apos/hair_front.png");
	sprite_.head= Novice::LoadTexture("./Resources/images/AnimResources/apos/head.png");
	sprite_.mask= Novice::LoadTexture("./Resources/images/AnimResources/apos/mask.png");
	sprite_.mask_eye= Novice::LoadTexture("./Resources/images/AnimResources/apos/mask_eye.png");
	sprite_.mouth = Novice::LoadTexture("./Resources/images/AnimResources/apos/mouth.png");
	sprite_.halfmask= Novice::LoadTexture("./Resources/images/AnimResources/apos/halfmask0.png");
	sprite_.eye_second = Novice::LoadTexture("./Resources/images/AnimResources/apos/eye_second.png");
	sprite_.body_second = Novice::LoadTexture("./Resources/images/AnimResources/apos/body_second.png");
	body_back=Novice::LoadTexture("./Resources/images/AnimResources/apos/body_back.png");
	sprite_.mask_eye_third= Novice::LoadTexture("./Resources/images/AnimResources/apos/mask_eye2.png");
	sprite_.halfmask_third= Novice::LoadTexture("./Resources/images/AnimResources/apos/halfmask.png");
	sprite_.armL_third= Novice::LoadTexture("./Resources/images/AnimResources/apos/armL_third.png");
	sprite_.armR_third = Novice::LoadTexture("./Resources/images/AnimResources/apos/armR_third.png");
	sprite_.body_third= Novice::LoadTexture("./Resources/images/AnimResources/apos/body_third.png");
	sprite_.mouth_dead=Novice::LoadTexture("./Resources/images/AnimResources/apos/mouth_dead.png");
	sprite_.mouth_third= Novice::LoadTexture("./Resources/images/AnimResources/apos/mouth_third.png");
}
