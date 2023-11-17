#pragma once
#include "Novice.h"
#include "ImGuiManager.h"
#include "Function/Function.h"
#include "Player/Player.h"
#include "UI/HpUI.h"
#include "UI/SpUI.h"
#include "UI/TimerUI.h"
#include "Item/PopItem.h"
#include <list>
#include "Object/Object.h"
#include "Enemy/PopEnemy.h"
#include "Back/BackGround.h"

/// <summary>
/// プレイシーンのクラス
/// </summary>

class GamePScene {
public:

	enum GameSMode {
		None, Pause, Option
		//何もなし,ポーズ
	};



	/// <summary>
	/// デストラクタ
	/// </summary>
	~GamePScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Wave& nowWave);

	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// Wave毎の挙動　チュートリアル
	/// </summary>
	void TutorialUpdate();

	/// <summary>
	/// Wave毎の挙動　Wave1
	/// </summary>
	void Wave1Update();

	/// <summary>
	/// Wave毎の挙動　Wave2
	/// </summary>
	void Wave2Update();

	/// <summary>
	/// Wave毎の挙動　Wave3
	/// </summary>
	void Wave3Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

	/// <summary>
	/// Wave毎の描写　チュートリアル
	/// </summary>
	void TutorialDraw();

	/// <summary>
	/// Wave毎の描写　Wave1
	/// </summary>
	void Wave1Draw();

	/// <summary>
	/// Wave毎の描写　Wave2
	/// </summary>
	void Wave2Draw();

	/// <summary>
	/// Wave毎の描写　Wave3
	/// </summary>
	void Wave3Draw();

	/// <summary>
	/// 当たり判定すべてを統括する関数
	/// </summary>
	void CheckCollisionAll();


	/// <summary>
	/// アイテムが消える関数
	/// </summary>
	void ItemDead();

	/// <summary>
	/// 敵が消える関数
	/// </summary>
	void EnemyDead();

	/// <summary>
	/// 敵が実際にポップする関数
	/// </summary>
	void EnemyPoping();

	/// <summary>
	/// Wave変更関数
	/// </summary>
	void WaveChange();

	///ゲッターセッター

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
	/// クリアとoverを判別するためのフラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetFlagGameOver() { return flagGameOver_; };

	/// <summary>
	/// 現在のwaveを受け取る
	/// </summary>
	/// <param name="nowWave"></param>
	Wave GetNowWave() { return nowWave_; };


private:
	// シーン変更できるかどうか
	bool flagChange_ = false;
	//クリアとoverを判別するためのフラグ
	bool flagGameOver_ = false;

	//仮挙動
	int CountNum_ = 0;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/// <summary>
	/// 現在のゲームのモード
	/// </summary>
	int gameSModeNow_ = None;

	const int changeTimingFrameMax_ = 10;
	int changeTimingFrame_ = 0;
	//ゲームをうごかしているか
	bool GameMove_ = false;

	//現在のwave(ここでWaveを管理するどこで再開か等)
	Wave nowWave_ = Tutorial;


	/// <summary>
	/// オブジェクト関連
	/// </summary>
	Player* player_ = nullptr;

	//Enemy* enemy_ = nullptr;
	//敵複数化
	std::list<PopEnemy*>enemy_;

	//敵がポップする間隔
	const int consEnemyPopFrame_ = 180;
	//敵がポップするまでを数える
	int EnemyPopFrame_ = consEnemyPopFrame_;


	HpUI* hpUi_ = nullptr;
	SpUI* spUi_ = nullptr;
	TimerUI* timerUi_ = nullptr;
	BackGround* backGround_ = nullptr;

	//アイテムポップ関数
	std::list<PopItem*>popItem_;
	//PopItem* popItem_;
};
