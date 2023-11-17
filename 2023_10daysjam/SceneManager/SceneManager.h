#pragma once

#include "ImGuiManager.h"
#include <stdint.h>
#include "Function/UtilityStruct.h"
//ここからシーン変換
#include "TitleScene.h"
#include "GamePScene.h"
#include "GameCScene.h"
#include "GameOScene.h"
#include "WaveSelect.h"

class SceneManager {
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ゲームモード
	/// </summary>
	enum SceneMode 
	{
		//タイトル,ゲームシーン、クリア、オーバー
		TitleMode, WaveSelectMode,GPlayMode, GClearMode, GOverMode
	};
	
	/// <summary>
	/// シーン管理変数のゲッター
	/// </summary>
	/// <returns></returns>
	uint32_t GetSceneNum() { return sceneNum_; };

	/// <summary>
	/// シーン管理変数のセッター
	/// </summary>
	/// <returns></returns>
	uint32_t SetSceneNum(uint32_t sceneNum) { this->sceneNum_ = sceneNum;};

	

private:
	// シーン
	uint32_t sceneNum_ = TitleMode;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//上からタイトル、ゲームシーン、クリア、オーバー
	TitleScene* title_ = nullptr;
	GamePScene* gameP_ = nullptr;
	GameCScene* gameC_ = nullptr;
	GameOScene* gameO_ = nullptr;
	WaveSelect* waveS_ = nullptr;

	// シーン変更できるかどうか
	bool flagChange_ = false;

	//waveの解除等と現在のwaveをつなぐ奴(プレイヤーが選択した奴)
	Wave nowWave_ = Tutorial;

	//プレイヤーが一番進んだ分(数を数えたいのでint)
	int maxWave_ = Tutorial;
};
