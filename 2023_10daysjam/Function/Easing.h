#pragma once
using namespace std;


enum EASE
{
	__EaseOutQuint,
	_EaseInQuint,
	___EaseInOutQuint,

	_EaseInCirc,
	__EaseOutCirc,
	___EaseInOutCirc,

	_EaseInSine,
	__EaseOutSine,
	___EaseInOutSine,

	_EaseInCubic,
	__EaseOutCubic,
	___EaseInOutCubic,

	_EaseInElastic,
	__EaseOutElastic,
	___EaseInOutElastic,

	_EaseInQuad,
	__EaseOutQuad,
	___EaseInOutQuad,

	_EaseInExpo,
	__EaseOutExpo,
	___EaseInOutExpo,

	_EaseInBack,
	__EaseOutBack,
	___EaseInOutBack,
};


float Easeing(const float& num, EASE easing);
/*
float EaseOutQuint(const float& num);

float EaseInOutCirc(const float& num);

float EaseInSine(const float& num);
float EaseOutSine(const float& num);
float EaseInOutSine(const float& num);

float EaseInOutBack(const float& num);
*/

