#pragma once
#include <Vector2.h>
#include <ScreenSize.h>
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/UtilityStruct.h"
#include "Function/Function.h"


class WaveTextUI
{
public:


	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Wave& nowWave);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Wave& nowWave);

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();
	void Draw(Vector2 ShakePos);

	/// <summary>
	/// 音鳴らす用
	/// </summary>
	void WaveChangeMusic();


private:

	//現在のウェーブ
	Wave nowWave_ = Tutorial;
	int nowWaveNum_ = (int)nowWave_;


	//左端
	IntState Lpos_ = { 50,150 };
	//右端
	IntState Rpos_ = { 0,0 };
	//画像
	int image_ = 0;
	//写したいサイズ
	const int sizeX_ = 125;
	const int sizeY_ = 64;

	//音源
	int changeEffect_ = 0;

	int changePlay_ = 0;

};

