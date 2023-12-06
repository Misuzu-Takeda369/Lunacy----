#pragma once
#include <Novice.h>
#include "Function/UtilityStruct.h"

//何個選択肢があるのか
const int selectNum_ = 4;

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

	void Initialize(int& maxWave);

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
	/// ロードの時の
	/// </summary>
	void ColorLode();

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
	/// 選択したwaveを受け取る
	/// </summary>
	/// <param name="nowWave"></param>
	Wave GetNowWave() { return nowWave_; };

private:
	// シーン変更できるかどうか
	bool flagChange_ = false;

	const int changeTimingFrameMax_ = 10;
	int changeTimingFrame_ = changeTimingFrameMax_;

	//waveの解除等と現在のwaveをつなぐ奴(プレイヤーが選択した奴)
	Wave nowWave_ = Tutorial;

	//プレイヤーが一番進んだ分(数を数えたいのでint)
	int maxWave_ = Tutorial;


	// キー入力結果を受け取る箱(多分デバック用)
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//マウスの位置(Yも無いと関数動かん)
	IntState mousePos_ = { 0,0 };

	
	//選択用の文字
	IntState selectLetter_[selectNum_];
	//表示用の色
	UnitColor selectColor_[selectNum_];

	//画像数
	int image_[selectNum_];
	int backImage_;


	//チュートリアル用の文字サイズ
	const IntState tutrialSize_={
		128,128
	};

	//文字用の文字サイズ
	const IntState textSize_ = {
		384,128
	};

};

