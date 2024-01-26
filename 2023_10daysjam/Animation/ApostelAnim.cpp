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
}

void ApostelAnim::Draw(unsigned int color)
{
	color;
	//Novice::DrawSprite((int)(_pos.x - _spriteRadius.x * _direction), (int)_pos.y - (int)(_spriteRadius.x ), rectTex_, 0.25f * _direction, 0.25f, 0, color_);
	// hair back
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.hair_back, WHITE, { 0.125f * _direction,0.125f }, 0);
	// head
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.head, WHITE, { 0.125f * _direction,0.125f }, 0);
	// face
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.eye, WHITE, { 0.125f * _direction,0.125f }, 0);
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mouth, WHITE, { 0.125f * _direction,0.125f }, 0);
	// hair side
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.hair_side, WHITE, { 0.125f * _direction,0.125f }, 0);
	// mask
	if (!maskBreak_) {
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mask, WHITE, { 0.125f * _direction,0.125f }, 0);
		DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.mask_eye, WHITE, { 0.125f * _direction,0.125f }, 0);
	}
	// hair front
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.hair_front, WHITE, { 0.125f * _direction,0.125f }, 0);
	// body
	DrawRotateScaleSprite(_pos, { 512.f,512.f }, 0, 0, sprite_.body, WHITE, { 0.125f * _direction,0.125f }, 0);
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
}
