#pragma once
#include <Vector2.h>
#include <ScreenSize.h>
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/UtilityStruct.h"
#include "ColorDefineEx.h"

class BHpUI
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int decreasedHp);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	//void Update(Wave nowWave);

	/// <summary>
	/// 前景描画
	/// </summary>
	//void Draw();
	void Draw(Vector2 ShakePos);

	/// <summary>
	/// ゲージ変換用パターン1
	/// </summary>
	//void ConversionUIVer1();

	/// <summary>
	/// ゲージ変換用パターン2
	/// </summary>
	void ConversionUIVer2();

	/// <summary>
	/// タイマーのゲッター
	/// </summary>
	/// <returns></returns>
	int GetterBossHp() { return hp_; };

	/// <summary>
	/// タイマーのセッター
	/// </summary>
	/// <returns></returns>
	void SetterBossHp(int timer) { hp_ = timer; };

	/// <summary>
	/// 移動量のリセット
	/// </summary>
	/// <param name="moveX"></param>
	void SetterMoveX(int moveX) { moveX_ = moveX; };

	void SetDicHp(int dichp) { hp_ = dichp; };

private:

	IntState bossHpUIPos_;

	int hp_;
	
	int bossHpDisplay_;

	//左端
	IntState Lpos_ = { 0,60 };
	//右端
	IntState Rpos_ = { 0,0 };
	//画像
	int image_ = 0;
	int frameImage_ = 0;
	//写したいサイズ
	const int sizeX_ = 500;
	const int sizeY_ = 32;

	//移動した合計
	int moveX_ = 0;
	//移動する量(HPが1減るたびに動く量)
	int moveSpeedX_ = 5;

	UnitColor color_;

	int keepstate = 0;
};

