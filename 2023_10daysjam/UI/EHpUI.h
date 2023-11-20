﻿#pragma once
#include <Vector2.h>
#include <ScreenSize.h>
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/UtilityStruct.h"


class EHpUI
{
public:

	//~HpUI();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(float decreasedHp, Vector2 pos);

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

private:

	//左端
	IntState Lpos_ = { 0,0 };
	//右端
	IntState Rpos_ = { 0,0 };
	//画像
	int image_ = 0;
	//int frameImage_ = 0;
	//写したいサイズ
	const int sizeX_ = 64;
	const int sizeY_ = 4;

	//移動した合計
	int moveX_ = 0;
	//移動する量(HPが1減るたびに動く量)
	int moveSpeedX_ = 5;

};

