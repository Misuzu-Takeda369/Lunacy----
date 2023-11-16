#pragma once
#include "Function/UtilityStruct.h"
#include <Novice.h>

class BackGround
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


private:

	int backImage_ = 0;
	int scaffoldImage_ = 0;

};

