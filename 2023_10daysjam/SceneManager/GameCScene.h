#pragma once
#include <Novice.h>
#include "Function/UtilityStruct.h"

/// <summary>
/// ゲームクリアシーンのクラス
/// </summary>

class GameCScene {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameCScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCScene();

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
	//受け取りのせいですぐに変わるのでそれを防ぐためのラグ(後で消える)
	int changeTimingFrame_ = 0;

	int gameClearImage_ = 0;
	int toTitleImage_ = 0;

	IntState toTitlePos_;
	const int textSizeX_ = 384;
	const int textSizeY_ = 128;

	UnitColor toTitleColor_ = { 255,255,255,255,0xFFFFFFFF };


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

};
