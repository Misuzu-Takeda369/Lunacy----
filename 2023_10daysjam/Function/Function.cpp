#include "Function.h"
#include "CharaBase.h"
float DegreeToRadian(float a) {
	float radian;
	radian = a * (float(M_PI) / 180.0f);
	return radian;
}

float RadianToDegree(float a)
{
	float degree;
	degree = a * (180.0f / float(M_PI));
	return degree;
}


int GetColorValue(int R, int G, int B, int A)
{
	unsigned int result;
	int r = R / 16; int g = G / 16; int b = B / 16; int a = A / 16;
	int r2 = R % 16; int g2 = G % 16; int b2 = B % 16; int a2 = A % 16;
	int r3 = (r * 0x10) + (r2 * 0x1);
	int g3 = (g * 0x10) + (g2 * 0x1);
	int b3 = (b * 0x10) + (b2 * 0x1);
	int a3 = (a * 0x10) + (a2 * 0x1);
	R = 0x1000000 * r3;
	G = 0x10000 * g3;
	B = 0x100 * b3;
	A = 0x1 * a3;
	result = R + G + B + A;
	return result;
}

int RandomRange(int min, int max)
{
	unsigned int range = 0;
	srand(int(time(nullptr) * rand()));
	srand(rand());
	if (min < 0) {
		range = max + (-min) + 1;

	}
	if (min > 0) {
		range = max - min + 1;
	}
	if (min == 0) {
		range = max + 1;
	}
	int num = rand() % range + min;
	return num;
}

bool CircleCollision(float aX, float aY, float aRadius, float bX, float bY, float bRadius) {
	float pos = (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY);
	float radius = (aRadius + bRadius) * (aRadius + bRadius);
	if (pos < radius) {
		return true;
	}
	else {
		return false;
	}
}

uint32_t AnimationNum(uint32_t animationNum, uint32_t maxFrame)
{

	animationNum++;
	if (animationNum >= maxFrame) {
		animationNum = 0;
	}

	return animationNum;
}


/*
Vector2 Normalize(const Vector2& v) {
	Vector2 result = { 0.0f,0.0f };

	float le = sqrt((v.x * v.x) + (v.y * v.y));

	if (le != 0.0f) {
		result.x = v.x / le;
		result.y = v.y / le;
	}

	return result;

}
*/

void TranslateWave(float& pos, const float& theta, float range1, float range2)
{
	float num = pos + (range1 * cosf(theta) + range2 * sinf(theta));
	pos = num;
}

void CircumferentialMovement(Vector2& v, const float& theta)
{
	const Vector2 v2 = v;
	v.x = v2.x * cosf(theta) - v2.y * sinf(theta);
	v.y = v2.y * cosf(theta) + v2.x * sinf(theta);
}

float DistanceSqrtf(float aX, float aY, float bX, float bY) {
	float dx = bX - aX;
	float dy = bY - aY;

	return (dx * dx) + (dy * dy);
}

bool IsCollisionCircleAndBox(Vector2 posA, float radiusA, Vector2 posB, float heigthB, float widthB)
{
	bool result=false;
	float leftB = posB.x - (widthB / 2);
	float rightB = posB.x + (widthB / 2);
	float topB = posB.y - (heigthB / 2);
	float bottomB = posB.y + (heigthB / 2);
	if ((posA.x > leftB - radiusA) && (posA.x < rightB + radiusA)) {
		if ((posA.y > topB - radiusA) && (posA.y < bottomB + radiusA)) {
			result = true;
			float f1 = radiusA * radiusA;
			if (posA.x < leftB) {
				if (posA.y < topB) {

					if ((DistanceSqrtf(leftB, topB, posA.x, posA.y) >= f1)) {
						result = false;
					}
					else {
						if (posA.y > bottomB) {
							if ((DistanceSqrtf(leftB, bottomB, posA.x, posA.y)>=f1)) {
								result = false;
							}
						}
					}
				}
			}
			else {
				if (posA.x > rightB) {
					if (posA.y < topB) {
						if (DistanceSqrtf(rightB, topB, posA.x, posA.y) >= f1) {
							result = false;
						}
					}
					else
					{
						if (posA.y > bottomB) {
							if (DistanceSqrtf(rightB, bottomB, posA.x, posA.y)>=f1) {
								result = false;
							}
						}
					}
				}
			}
		}
	}
	return result;
}

bool IsCollisonBox(Vector2 posA, float heigthA, float widthA, Vector2 posB, float heigthB, float widthB)
{

	//A
	float leftA = posA.x - (widthA / 2);
	float rightA = posA.x + (widthA / 2);
	float topA = posA.y - (heigthA / 2);
	float bottomA = posA.y + (heigthA / 2);
	//B
	float leftB = posB.x - (widthB / 2);
	float rightB = posB.x + (widthB / 2);
	float topB = posB.y - (heigthB / 2);
	float bottomB = posB.y + (heigthB / 2);

	if (leftB < rightA && leftA < rightB) {
		if (topB < bottomA && topA < bottomB) {
			return true;
		}
	}
	return false;
}

bool IsCollision(Object* objA,Object* objB)
{
	CollisionType typeA = objA->GetCollisionType();
	CollisionType typeB = objB->GetCollisionType();
	CharaBase charaA = objA->GetCharaBase();
	CharaBase charaB = objB->GetCharaBase();
	bool result = false;

	if (typeA == None) {
		return false;
	}

	if (typeA == Circle) {
		if (typeB == Circle) {

			result = CircleCollision(charaA.pos_.x, charaA.pos_.y, charaA.radius_,
				charaB.pos_.x, charaB.pos_.y, charaB.radius_);
		}
		else if (typeB == Box) {
			Vector2 sizeB = objB->GetBoxSize();
			result = IsCollisionCircleAndBox(charaA.pos_, charaA.radius_, charaB.pos_, sizeB.y, sizeB.x);
		}
	}

	else if (typeA == Box) {
		if (typeB == Circle) {
			Vector2 sizeA = objA->GetBoxSize();
			result = IsCollisionCircleAndBox(charaB.pos_, charaB.radius_, charaA.pos_, sizeA.y, sizeA.x);
		}
		else if (typeB == Box) {
			Vector2 sizeA = objA->GetBoxSize();
			Vector2 sizeB = objB->GetBoxSize();
			result = IsCollisonBox(charaA.pos_, sizeA.y, sizeA.x, charaB.pos_, sizeB.y, sizeB.x);
		}
	}

	return result;
}

void DrawRotateSprite(Vector2 pos, Vector2 size, int srcX, int srcY, int textureHandle, unsigned int color, float theta)
{
	struct Vector2Int
	{
		int x; int y;
	};
	Vector2 lTop = {//left top
		-size.x,
		-size.y
	};
	Vector2 rTop = {//right top
		+size.x,
		-size.y
	};
	Vector2 lBottom = {//left bottom
		-size.x,
		+size.y
	};
	Vector2 rBottom = {//right bottom
		+size.x,
		+size.y
	};

	float LeftTopRotated_x = float(lTop.x * cosf(theta) - lTop.y * sinf(theta));
	float LeftTopRotated_y = lTop.y * cosf(theta) + lTop.x * sinf(theta);
	float LeftBottomRotated_x = lBottom.x * cosf(theta) - lBottom.y * sinf(theta);
	float LeftBottomRotated_y = lBottom.y * cosf(theta) + lBottom.x * sinf(theta);
	float RightTopRotated_x = rTop.x * cosf(theta) - rTop.y * sinf(theta);
	float RightTopRotated_y = rTop.y * cosf(theta) + rTop.x * sinf(theta);
	float RightBottomRotated_x = rBottom.x * cosf(theta) - rBottom.y * sinf(theta);
	float RightBottomRotated_y = rBottom.y * cosf(theta) + rBottom.x * sinf(theta);

	Vector2Int lTopPos = {//left top
		(int)LeftTopRotated_x + (int)pos.x,
		(int)LeftTopRotated_y + (int)pos.y
	};
	Vector2Int rTopPos = {//right top
		 (int)RightTopRotated_x + (int)pos.x ,
		 (int)RightTopRotated_y + (int)pos.y
	};
	Vector2Int lBottomPos = {//left bottom
		(int)LeftBottomRotated_x + (int)pos.x ,
		(int)LeftBottomRotated_y + (int)pos.y
	};
	Vector2Int rBottomPos = {//right bottom
		(int)RightBottomRotated_x + (int)pos.x ,
		(int)RightBottomRotated_y + (int)pos.y
	};

	Novice::DrawQuad(lTopPos.x, lTopPos.y, rTopPos.x, rTopPos.y, lBottomPos.x, lBottomPos.y, rBottomPos.x, rBottomPos.y
		, srcX, srcY, (int)size.x, (int)size.y, textureHandle, color);
}

void DrawRotateScaleSprite(Vector2 pos, Vector2 size, int srcX, int srcY, int textureHandle, unsigned int color, float scale, float theta)
{
	struct Vector2Int
	{
		int x; int y;
	};
	Vector2 lTop = {//left top
		-size.x * scale,
		-size.y * scale
	};
	Vector2 rTop = {//right top
		+size.x * scale,
		-size.y * scale
	};
	Vector2 lBottom = {//left bottom
		-size.x * scale,
		+size.y * scale
	};
	Vector2 rBottom = {//right bottom
		+size.x * scale,
		+size.y * scale
	};

	float LeftTopRotated_x = float(lTop.x * cosf(theta) - lTop.y * sinf(theta));
	float LeftTopRotated_y = lTop.y * cosf(theta) + lTop.x * sinf(theta);
	float LeftBottomRotated_x = lBottom.x * cosf(theta) - lBottom.y * sinf(theta);
	float LeftBottomRotated_y = lBottom.y * cosf(theta) + lBottom.x * sinf(theta);
	float RightTopRotated_x = rTop.x * cosf(theta) - rTop.y * sinf(theta);
	float RightTopRotated_y = rTop.y * cosf(theta) + rTop.x * sinf(theta);
	float RightBottomRotated_x = rBottom.x * cosf(theta) - rBottom.y * sinf(theta);
	float RightBottomRotated_y = rBottom.y * cosf(theta) + rBottom.x * sinf(theta);

	Vector2Int lTopPos = {//left top
		(int)LeftTopRotated_x + (int)pos.x,
		(int)LeftTopRotated_y + (int)pos.y
	};
	Vector2Int rTopPos = {//right top
		 (int)RightTopRotated_x + (int)pos.x ,
		 (int)RightTopRotated_y + (int)pos.y
	};
	Vector2Int lBottomPos = {//left bottom
		(int)LeftBottomRotated_x + (int)pos.x ,
		(int)LeftBottomRotated_y + (int)pos.y
	};
	Vector2Int rBottomPos = {//right bottom
		(int)RightBottomRotated_x + (int)pos.x ,
		(int)RightBottomRotated_y + (int)pos.y
	};

	Novice::DrawQuad(lTopPos.x, lTopPos.y, rTopPos.x, rTopPos.y, lBottomPos.x, lBottomPos.y, rBottomPos.x, rBottomPos.y
		, srcX, srcY, (int)size.x, (int)size.y, textureHandle, color);
}


Vector2 AdjustSpriteScale(Vector2 spriteSize, Vector2 radius) {
	//Vector2 num = {
	//num.x = 1 / radius.x,
	//num.y = 1 / radius.y };

	Vector2 num2 = {
		num2.x = spriteSize.x / radius.x,
		num2.y = spriteSize.y / radius.y,
	};

	Vector2 divNum2{
		divNum2.x = 1 / num2.x,
		divNum2.y = 1 / num2.y,
	};

	return divNum2;
}

float AdjustSpriteScale(float spriteSize, float radius) {

	//float num = 1 / radius;
	float num2 = spriteSize / radius;
	float result = 1 / num2;
	return result;
}