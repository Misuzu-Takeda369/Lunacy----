#include "Easing.h"
#define _USE_MATH_DEFINES
#include <cmath>
static const float c1 = 1.70158f;
static const float c2 = c1 * 1.525f;
static const float c3 = c1 + 1.0f;
static const float c4 = (2.0f * (float)M_PI) / 3.0f;
static const float c5 = (2.0f * (float)M_PI) / 4.5f;

//Quint
float EaseInQuint(const float& num);
float EaseOutQuint(const float& num);
float EaseInOutQuint(const float& num);

//Circ
float EaseInCirc(const float& num);
float EaseOutCirc(const float& num);
float EaseInOutCirc(const float& num);

//Sine
float EaseInSine(const float& num);
float EaseOutSine(const float& num);
float EaseInOutSine(const float& num);

//Cubic
float EaseInCubic(const float& num);
float EaseOutCubic(const float& num);
float EaseInOutCubic(const float& num);

//Elastic
float EaseInElastic(const float& num);
float EaseOutElastic(const float& num);
float EaseInOutElastic(const float& num);

//Quad
float EaseInQuad(const float& num);
float EaseOutQuad(const float& num);
float EaseInOutQuad(const float& num);

//Quart(未)
float EaseInQuart(const float& num);
float EaseOutQuart(const float& num);
float EaseInOutQuart(const float& num);

//Expo
float EaseInExpo(const float& num);
float EaseOutExpo(const float& num);
float EaseInOutExpo(const float& num);

//Back
float EaseInBack(const float& num);
float EaseOutBack(const float& num);
float EaseInOutBack(const float& num);

//Bounce(未)
float EaseInBounce(const float& num);
float EaseOutBounce(const float& num);
float EaseInOutBounce(const float& num);



/// <summary>
/// イージング関数
/// </summary>
/// <param name="num">0.0～1.0</param>
/// <param name="easing">イージング関数</param>
/// <returns></returns>
float Easeing(const float& num, EASE easing)
{
	switch (easing)
	{
//Quint
	case _EaseInQuint:
		return EaseInQuint(num);
		break;
	case __EaseOutQuint:
		return EaseOutQuint(num);
		break;
	case ___EaseInOutQuint:
		return EaseInOutQuint(num);

//Circ
	case _EaseInCirc:
		return EaseInCirc(num);
	case __EaseOutCirc:
		return EaseOutCirc(num);
	case ___EaseInOutCirc:
		return EaseInOutCirc(num);
		break;

//Sine
	case _EaseInSine:
		return EaseInSine(num);
		break;
	case __EaseOutSine:
		return EaseOutSine(num);
		break;
	case ___EaseInOutSine:
		return EaseOutSine(num);
		break;

//Cubic
	case _EaseInCubic:
		return EaseInCubic(num);
	case __EaseOutCubic:
		return EaseOutCubic(num);
	case ___EaseInOutCubic:
		return EaseInOutCubic(num);

//Elastic
	case _EaseInElastic:
		return EaseInElastic(num);
	case __EaseOutElastic:
		return EaseOutElastic(num);
	case ___EaseInOutElastic:
		return EaseInOutElastic(num);

//Quad
	case _EaseInQuad:
		return EaseInQuad(num);
	case __EaseOutQuad:
		return EaseOutQuad(num);
	case ___EaseInOutQuad:
		return EaseInOutQuad(num);

//Expo
	case _EaseInExpo:
		return EaseInExpo(num);
	case __EaseOutExpo:
		return EaseOutExpo(num);
	case ___EaseInOutExpo:
		return EaseInOutExpo(num);

//Back
	case _EaseInBack:
		return EaseInBack(num);
	case __EaseOutBack:
		return EaseOutBack(num);
	case ___EaseInOutBack:
		return EaseInOutBack(num);
		break;

	default:
		break;
	}
	return 0.0f;
}

float EaseInQuint(const float& num)
{
	return num * num * num * num * num;
}

float EaseOutQuint(const float& num)
{
	return 1 - powf(1-num,5);
}

float EaseInOutQuint(const float& num)
{
	return num < 0.5f
		? 16.0f * num * num * num * num * num
		: 1.0f - pow(-2.0f * num + 2.0f, 5.0f) / 2.0f;
}

float EaseInCirc(const float& num)
{
	return 1.0f - sqrtf(1.0f - powf(num, 2.0f));
}

float EaseOutCirc(const float& num)
{
	return sqrtf(1.0f - powf(num - 1.0f, 2.0f));
}

float EaseInOutCirc(const float& num)
{
	return num < 0.5f ? (1.0f - sqrtf(1 - powf(2.0f * num, 2.0f))) / 2.0f : (sqrtf(1 - powf(-2.0f * num + 2.0f, 2.0f)) + 1.0f) / 2.0f;
}

float EaseInSine(const float& num)
{
	return 1 - cosf((num * (float)M_PI) / 2.0f);
}

float EaseOutSine(const float& num)
{
	return sinf((num * (float)M_PI) / 2.0f);
}

float EaseInOutSine(const float& num)
{
	return -(cosf((float)M_PI * num) - 1.0f) / 2.0f;
}

float EaseInCubic(const float& num)
{
	return num*num*num;
}

float EaseOutCubic(const float& num)
{
	return 1.0f - powf(1.0f - num, 3.0f);
}

float EaseInOutCubic(const float& num)
{
	return num < 0.5f
		? 4 * num * num * num
		: 1 - powf(-2.0f * num + 2.0f, 3.0f) / 2.0f;
}

float EaseInElastic(const float& num)
{
	return num == 0.0f
		? 0.0f
		: num == 1.0f
		? 1.0f
		: -powf(2.0f, 10.0f * num - 10.0f) * sinf((10.0f - 10.75f) * c4);
}

float EaseOutElastic(const float& num)
{
	return num == 0.0f
		? 0.0f
		: num == 1.0f
		? 1.0f
		: powf(2.0f, -10.0f * num) * sinf((num * 10.0f - 0.75f) * c4) + 1.0f;
}

float EaseInOutElastic(const float& num)
{
	return num == 0.0f
		? 0.0f
		: num == 1.0f
		? 1.0f
		: num < 0.5f
		? -(powf(2.0f, 20.0f * num - 10.0f) * sinf((20.0f * num - 11.125f) * c5)) / 2.0f
		: (powf(2.0f, -20.0f * num + 10.0f) * sinf((20.0f * num - 11.125f) * c5)) / 2.0f + 1.0f;
}

float EaseInQuad(const float& num)
{
	return num*num;
}

float EaseOutQuad(const float& num)
{
	return 1.0f - (1.0f - num) * (1.0f - num);
}

float EaseInOutQuad(const float& num)
{
	return num < 0.5f
		? 2.0f * num * num
		: 1 - pow(-2 * num + 2.0f, 2.0f) / 2.0f;
}

float EaseInExpo(const float& num)
{
	return num == 0.0f
		? 0
		: powf(2.0f, 10.0f * num - 10.0f);
}

float EaseOutExpo(const float& num)
{
	return num == 1.0f
		? 1.0f
		: 1.0f - powf(2.0f, -10.0f * num);
}

float EaseInOutExpo(const float& num)
{
	return num == 0.0f
		? 0.0f
		: num == 1.0f
		? 1.0f
		: num < 0.5f
		? powf(2.0f, 20 * num - 10.0f) / 2.0f
		: (2.0f - powf(2.0f, -20.0f * num + 10.0f)) / 2.0f;
}

float EaseInBack(const float& num)
{
	return c3 * num * num * num - c1 * num * num;
}

float EaseOutBack(const float& num)
{
	return 1.0f + c3 * powf(num - 1.0f, 3.0f) + c1 * powf(num - 1.0f, 2.0f);
}

float EaseInOutBack(const float& num)
{
	
	return num < 0.5
		? (powf(2.0f * num, 2.0f) * ((c2 + 1.0f) * 2.0f * num - c2)) / 2.0f
		: (powf(2.0f * num - 2.0f, 2.0f) * ((c2 + 1.0f) * (num * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
}
