#pragma once
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/Function.h"

class TutrialText
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
	/// 現在使っている画像numを受け取る
	/// </summary>
	/// <param name="imageNum">現在の画像num</param>
	void SetImageNum(int imageNum) {
		imageNum_ = imageNum;
	};

private:


	int textFrameImage_;
	int textImage_;

	//テキストの現在のnum
	int imageNum_;

	//1パーツのサイズ
	const IntState imageSize_={
		650 , 280
	};

	//表示するときの縦からn番目横からn番目を表す奴(x0~3 y0~ 2)
	IntState DisplayNum = {
		0 , 0
	};
};

