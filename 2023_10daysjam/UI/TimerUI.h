#pragma once
#include <Vector2.h>
#include <ScreenSize.h>
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/UtilityStruct.h"

class TimerUI
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ゲージ変換用パターン1
	/// </summary>
	void ConversionUIVer1();

	/// <summary>
	/// ゲージ変換用パターン2
	/// </summary>
	void ConversionUIVer2();

	/// <summary>
	/// タイマーのゲッター
	/// </summary>
	/// <returns></returns>
	int GetterTimer() { return timer_; };

private:

	IntState timerUIPos_;
	
	int timer_;
	int timerMaxDis_;
	int timerDisplay_;

	//左端
	IntState Lpos_ = { 0,60 };
	//右端
	IntState Rpos_ = { 0,0 };
	//画像
	int image_ = 0;
	//写したいサイズ
	const int sizeX_ = 500;
	const int sizeY_ = 32;

	//移動した合計
	int moveX_ = 0;
	//移動する量(HPが1減るたびに動く量)
	int moveSpeedX_ = 9;
};