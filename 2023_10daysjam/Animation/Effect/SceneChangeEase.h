#pragma once
#include "Function/UtilityStruct.h"
#include <Novice.h>
/// <summary>
/// シーンが変わる時のイージングクラス
/// マネージャーにくっつける
/// 四角の内側から徐々に大きくなる奴
/// </summary>
class SceneChangeEase
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描写
	/// </summary>
	void Draw();

private:

	//■の左端位置
	IntState pos_;

	//■を徐々に
	float scale_;
	//正方形で考えているのでこちらで1280*1280
	const int size_ = 1280;

	const float maxScale = 1.0f;
	const float mimScale = 0.0f;

	//念のための色
	UnitColor color_;

};

