#pragma once
#include <Novice.h>
#include "Function/UtilityStruct.h"

class WaveSelect
{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	WaveSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WaveSelect();

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
	/// マウスでのシーン変換
	/// </summary>
	void MouseBottonChack();

	/// <summary>
	/// シーン変更管理のゲッター
	/// </summary>
	/// <returns></returns>
	bool GetFlagChange() { return flagChange_; };

	/// <summary>
	/// シーン変更管理のセッター
	/// </summary>
	/// <returns></returns>
	bool SetFlagChange(bool flagChange) { return this->flagChange_ = flagChange; };

private:
	// シーン変更できるかどうか
	bool flagChange_ = false;

	int changeTimingFrame_ = 0;

	// キー入力結果を受け取る箱(多分デバック用)
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//マウスの位置(Yも無いと関数動かん)
	IntState mousePos_ = { 0,0 };

};

