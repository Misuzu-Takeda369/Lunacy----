#include "Animation/Effect/LunaMental.h"
#include "Function/Function.h"
#include "Novice.h"
#include "Function/Easing.h"

LunaMentalEffect::LunaMentalEffect()
{
}

LunaMentalEffect::~LunaMentalEffect()
{
}

 void LunaMentalEffect::Initialize(Vector2 pos)
{
	_standard = pos;
	_digree = RandomRange(0, 359);
	_effectRange = (float)RandomRange(10, 20);
	if (_side != 1 && _side != 2) {
		_effectRange = (float)RandomRange(40, 60);
	}
	_radian = DegreeToRadian((float)_digree);
	_target.x = (_effectRange * cosf(_radian) - _effectRange * sinf(_radian)) + pos.x;
	_target.y = (_effectRange * cosf(_radian) + _effectRange * sinf(_radian)) + pos.y;
	_color = {
		RandomRange(50,150),
		0,
		RandomRange(50,150),
		255,
	};
	
	_radius = RandomRange(5, 15);
	_isArrive = true;
	_t = 0;
	_direction = 1.0f;
	if (RandomRange(1, 2) == 2) {
		_direction = -1.0f;
	}
	_side = RandomRange(1, 3);
	
	_image = 0;
	_Scale = (float)RandomRange(1, 3);
}

 void LunaMentalEffect::Update(Vector2 pos)
 {
	 _playerPos = pos;
	 if (_t > 1 || _color.A <= 0) {
		 _isArrive = false;
		 _color.A = 0;
		 return;
	 }
	 else {
		 _color.A -= 5;
	 }

	 _color.color = GetColorValue(_color.R, _color.G, _color.B, _color.A);

	 _t += 0.01f;
	 if (_side == 1) {
		 _pos.x = (1.0f - _t) * _standard.x * (1 + Easeing(_t, __EaseOutQuint) * 0.5f * _direction) + _t * _target.x;
		 _pos.y = (1.0f - _t) * _standard.y  + _t * _target.y;
	 }
	 else if(_side==2) {
		 _pos.x = (1.0f - _t) * _standard.x  + _t * _target.x;
		 _pos.y = (1.0f - _t) * _standard.y * (1 + Easeing(_t, __EaseOutQuint) * 0.25f * _direction) + _t * _target.y;
	 }
	 else {
		 _pos.x = (1.0f - _t) * _standard.x + _t * _target.x;
		 _pos.y = (1.0f - _t) * _standard.y  + _t * _target.y;
	 }
	 // _pos.x=Easeing(_t, _EaseInCubic);
	 // _pos.y=Easeing(_t,_EaseInCubic);
 }

void LunaMentalEffect::Draw()
{
	//Novice::DrawEllipse((int)_pos.x, (int)_pos.y, _radius, _radius, 0, _color.color, kFillModeSolid);
	
	Novice::DrawSprite((int)_pos.x, (int)_pos.y, _image, _Scale, _Scale,0.0f, _color.color);
}
