#pragma once
#include <Novice.h>
#include "Function/UtilityStruct.h"

class BGMManage
{

public:

	/// <summary>
	/// 初期化(ロード)
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新ここで音楽を流す
	/// </summary>
	void Update(float& Hp,float& Sp,Wave& NowWave);

	/// <summary>
	/// 曲を止める用関数
	/// </summary>
	void StopBGM();

	void PauseBGM();

private:

	//音
	int nomalBGM_ = 0;
	int bossBGM_ = 0;
	int dangerBGM_ = 0;

	//ハンドル
	int nomalPlay_ = -1;
	int bossPlay_ = -1;
	int dangerPlay_ = -1;

	//この値になったらBGMカエル
	const float ChangeBGM = 200.0f;
};

