#pragma once
#include "Vector2.h"
#include "Function/UtilityStruct.h"
class LunaMentalEffect
{
public:
	LunaMentalEffect();
	~LunaMentalEffect();
	void Initialize(Vector2 pos);
	void Update(Vector2 pos);
	void Draw();
	bool GetIsArrive() { return _isArrive; }



private:
	Vector2 _pos;
	Vector2 _playerPos;
	Vector2 _target;
	Vector2 _standard;
	float _t;
	int _digree;
	float _radian;
	float _effectRange;
	UnitColor _color;
	bool _isArrive = true;
	float _direction = 1.0f;
	int _side = 0;
	int _radius = 10;
	float _radi;
	uint32_t sprite_;


};



