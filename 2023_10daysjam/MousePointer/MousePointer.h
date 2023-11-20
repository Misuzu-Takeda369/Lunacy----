#pragma once
#include <Novice.h>
#include "Function/UtilityStruct.h"

class MousePointer
{
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>
	MousePointer();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MousePointer();

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

private:

	//マウスの位置(Yも無いと関数動かん)
	IntState mousePos_ = { 0,0 };

	//画像のサイズ
	const IntState pointerSize = {64,64};

	int pointerImage_;

};

