#pragma once
#include "Function/UtilityStruct.h"
#include <Novice.h>
/// <summary>
/// シーンが変わる時のイージングクラス
/// マネージャーにくっつける
/// 四角の内側から徐々に大きくなる奴
/// </summary>

/// <summary>
/// 現在のフラグ
/// </summary>
enum ChangeMode {
	Nochange,Before,After
};

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

	/// <summary>
	/// シーン変更前
	/// </summary>
	void ChangeBefore();

	/// <summary>
	/// シーン変更後
	/// </summary>
	void ChangeAfter();

	/// <summary>
	/// セッター(シーン変わる前か後か画面が暗いか否か) 
	/// </summary>
	/// <param name="noweffect">ここに後か前か入れる</param>
	void SetNowEffectMode(ChangeMode noweffect) {
		nowEffectMode_ = noweffect;
	}

	/// <summary>
	/// ゲッター(シーン変わる前か後か画面が暗いか否か) 
	/// </summary>
	ChangeMode GetNowEffectMode() {
		return nowEffectMode_;
	}

private:

	//■の左端位置
	IntState pos_;

	//■を徐々に
	int scale_;
	//正方形で考えているのでこちらで1280*1280
	const int maxsize_ = 1280;
	const int mimsize_ = 0;


	const int maxScale = 200;
	const int mimScale = 0;

	int size_ = 10;

	//念のための色
	UnitColor color_;

	//モード
	ChangeMode nowEffectMode_ = Nochange;

};

