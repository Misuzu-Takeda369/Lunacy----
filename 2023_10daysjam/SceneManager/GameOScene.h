#pragma once
#include <Novice.h>
#include "Function/UtilityStruct.h"

/// <summary>
/// ゲームオーバーシーンのクラス
/// </summary>

class GameOScene
{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameOScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameOScene();

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

	/// <summary>
	/// リトライするかを判別するためのフラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetFlagRetry() { return flagRetry_; };

private:
	// シーン変更できるかどうか
	bool flagChange_ = false;


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//受け取りのせいですぐに変わるのでそれを防ぐためのラグ(後で消える)
	int changeTimingFrame_ = 0;

	//リトライするかを判別するためのフラグ
	bool flagRetry_ = false;

	int gameOverImage_ = 0;
	int retryImage_ = 0;
	int toTitleImage_ = 0;

	IntState retryPos_;
	IntState toTitlePos_;
	const int textSizeX_ = 384;
	const int textSizeY_ = 128;


	//マウスの位置(Yも無いと関数動かん)
	IntState mousePos_ = { 0,0 };
	UnitColor retryColor_ = { 255,255,255,255,0xFFFFFFFF };
	UnitColor toTitleColor_ = { 255,255,255,255,0xFFFFFFFF };
};
