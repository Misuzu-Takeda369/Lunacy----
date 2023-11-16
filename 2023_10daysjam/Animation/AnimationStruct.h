#pragma once
#include "Vector2.h"

struct Quad
{
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;
};

struct TextureSet
{
	unsigned int sprite = (int)nullptr;
	unsigned int sprite1 = (int)nullptr;
	unsigned int sprite2 = (int)nullptr;
	unsigned int sprite3 = (int)nullptr;
	unsigned int head = (int)nullptr;
	unsigned int leftArm = (int)nullptr;
	unsigned int rightArm = (int)nullptr;
	unsigned int leftLeg = (int)nullptr;
	unsigned int rightLeg = (int)nullptr;
	unsigned int tail = (int)nullptr;
	unsigned int weapon = (int)nullptr;
	unsigned int body = (int)nullptr;

};

struct TexturePos
{
	Vector2 sprite;
	Vector2 sprite1;
	Vector2 sprite2;
	Vector2 sprite3;
	Vector2 head = { 0,0 };
		Vector2 leftArm;
		Vector2 rightArm;
		Vector2 leftLeg;
		Vector2 rightLeg;
		Vector2 tail;
		Vector2 weapon;
		Vector2 body = {0,0};
};
