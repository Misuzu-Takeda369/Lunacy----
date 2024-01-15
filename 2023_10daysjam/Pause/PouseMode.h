#pragma once
#include <Novice.h>
#include "ScreenSize.h"
#include "Function/UtilityStruct.h"
#include "Vector2.h"
#include "ColorDefineEx.h"

/// <summary>
/// ポーズ関連のクラス
/// </summary>
class PouseMode
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="gameSModeNow">現在のゲームモード</param>
	void Update(int gameSModeNow);

	/// <summary>
	/// 描写
	/// </summary>
	/// /// <param name="gameSModeNow">現在のゲームモード</param>
	void Draw(int gameSModeNow,Vector2 ShakePos);

	/// <summary>
	/// 確認の更新
	/// </summary>
	void ChackUpdate();

	/// <summary>
	/// 確認の描写
	/// </summary>
	void ChackDraw();

	/// <summary>
	/// モードのゲッター
	/// </summary>
	/// <returns></returns>
	int GetGameSModeNow() {
		return gameSModeNow_;
	};

	/// <summary>
	/// フラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetChangeFrag() {
		return changeFrag_;
	}

	/// <summary>
	/// フラグのセッター
	/// </summary>
	/// <param name="flag"></param>
	void SetChangeFrag(bool flag) {
		changeFrag_ = flag;
	}

	/// <summary>
	/// タイトルに戻るフラグ
	/// </summary>
	/// <returns></returns>
	bool GettitleChangeFrag() {
		return titleChangeFrag_;
	}

private:

	//ポーズ文字(ゲーム画面)
	int imageGMPauseText_;
	//ポーズ文字(ポーズ画面)
	//int imagePMPauseText_;
	//ゲーム画面に戻る
	int imagePlayBackText_;
	//タイトルに戻る
	int imageTitleBackText_;

	int yesImage_;
	int noImage_;
	int textFrameImage_;
	int chacktextImage_;


	//ゲームモードの時に出てくる文字の奴
	IntState GMPauseTextPos_;

	//画像サイズ
	const IntState size_ = {
		256,128
	};

	UnitColor imageColor_ = {0,0,0,0,0xFFFFFFFF};

	UnitColor PimageColor_[2] = { {0,0,0,0,0xFFFFFFFF},{0,0,0,0,0xFFFFFFFF} };

	//チェック用
	UnitColor chackColor_[2] = { {0,0,0,0,0xFFFFFFFF},{0,0,0,0,0xFFFFFFFF} };

	//ポーズモードの時に出てくる文字の奴
	IntState PMPauseTextPos_[3];

	//確認時に出てくる文字の奴
	IntState chackTextPos_[2];

	//マウスの位置
	IntState mousePos_ = { 0,0 };

	//モード
	int gameSModeNow_;

	///フラグ(ポーズとゲームか)
	bool changeFrag_ = false;
	//タイトルに戻るフラグ
	bool titleChangeFrag_ = false;
	//確認
	bool chackFrage_ = false;

};

