#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cstdint>
#include "Vector2.h"
#include "Object/Object.h"

/// <summary>
/// 角度の変換
/// </summary>
/// <param name="a">degree(0～360°)</param>
/// <returns></returns>
float DegreeToRadian(float a);

/// <summary>
/// 角度の変換
/// </summary>
/// <param name="a">radian</param>
/// <returns></returns>
float RadianToDegree(float a);

/// <summary>
/// 色の設定(返り値) 10進数を入力
/// </summary>
/// /// <param name="R">Rの値</param>
/// /// <param name="G">Gの値</param>
/// /// <param name="B">Bの値</param>
/// /// <param name="A">Aの値</param>
/// <returns></returns>
int GetColorValue(int R, int G, int B, int A);

/// <summary>
/// 整数で範囲をランダムに出す(もしかしたらバグあるかも)
/// </summary>
/// <param name="min">最小値</param>
/// <param name="max">最大値</param>
/// <returns></returns>
int RandomRange(int min, int max);

/// <summary>
/// 円の衝突判定
/// </summary>
/// <param name="aX">円１　x</param>
/// <param name="aY">円１　y</param>
/// <param name="aRadius">円１　半径</param>
/// <param name="bX">円２　x</param>
/// <param name="bY">円２　y</param>
/// <param name="bRadius">円２　半径</param>
/// <returns></returns>
bool CircleCollision(float aX, float aY, float aRadius, float bX, float bY, float bRadius);


/// <summary>
/// アニメーション変化関数
/// </summary>
/// <param name="animationNum">何番目かの変数</param>
/// /// <param name="maxFrame">アニメーションの合計フレーム数</param>
/// <returns></returns>
uint32_t AnimationNum(uint32_t animationNum, uint32_t maxFrame);


/// <summary>
/// 正規化
/// </summary>
/// <param name="v">正規化したい値</param>
/// <returns></returns>
//Vector2 Normalize(const Vector2& v);

void TranslateWave(float& pos, const float& theta, float range1, float range2);

/// <summary>
/// 円周移動 
/// </summary> 
/// <param name="v"></param>
/// <param name="theta"></param>
void CircumferentialMovement(Vector2& v, const float& theta);

/// <summary>
/// オブジェクト同士の衝突判定(矩形の座標は中心基準)
/// </summary>
/// <param name="objA">オブジェクト1</param>
/// <param name="objB">オブジェクト2</param>
/// <returns></returns>
bool IsCollision(Object* objA, Object* objB);

/// <summary>
/// スプライトを回転させたいときに
/// </summary>
/// <param name="pos">座標(中心)</param>
/// <param name="size">画像サイズ(1フレーム分)</param>
/// <param name="srcX">画像上で表示する左上座標X</param>
/// <param name="srcY">画像上で表示する左上座標Y</param>
/// <param name="textureHandle">テクスチャハンドル</param>
/// <param name="color">色</param>
/// <param name="theta">回転角度?</param>
void DrawRotateSprite(Vector2 pos, Vector2 size, int srcX, int srcY, int textureHandle,
	unsigned int color, float theta);


////// <summary>
/// スプライトを拡縮/回転させたいときに
/// </summary>
/// <param name="pos">座標(中心)</param>
/// <param name="size">画像サイズ(1フレーム分)</param>
/// <param name="srcX">画像上で表示する左上座標X</param>
/// <param name="srcY">画像上で表示する左上座標Y</param>
/// <param name="textureHandle">テクスチャハンドル</param>
/// <param name="color">色</param>
/// <param name="scale">拡大率</param>
/// <param name="theta">回転角度(ラジアン)</param>
void DrawRotateScaleSprite(Vector2 pos, Vector2 size, int srcX, int srcY, int textureHandle, unsigned int color, float scale, float theta);
void DrawRotateScaleSprite(Vector2 pos, Vector2 size, int srcX, int srcY, int textureHandle, unsigned int color, Vector2 scale, float theta);

Vector2 AdjustSpriteScale(Vector2 spriteSize, Vector2 radius);
float AdjustSpriteScale(float spriteSize, float radius);
