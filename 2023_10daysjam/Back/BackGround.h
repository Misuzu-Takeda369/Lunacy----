#pragma once
#include "Function/UtilityStruct.h"
#include <Novice.h>
#include <vector2.h>

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

	void SetPlayerSP(float sp,float maxSP);
	void Draw(Vector2 ShakePos);

private:

	int backImage_ = 0;
	int scaffoldImage_ = 0;

	//低sp
	unsigned int backLowSPImage_;
	unsigned int backMidiamSPImage_;
	int playerMaxSP_;
	int playerSP_;

};

