#pragma once
#include "Function/UtilityStruct.h"
#include <Vector2.h>
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

	void Draw(Vector2 ShakePos);


private:

	int backImage_ = 0;
	int scaffoldImage_ = 0;

};

