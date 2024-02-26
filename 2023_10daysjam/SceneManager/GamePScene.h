﻿#pragma once
#include "Novice.h"
#include "ImGuiManager.h"
#include "Function/Function.h"
#pragma region UI
#include "UI/HpUI.h"
#include "UI/SpUI.h"
#include "UI/TimerUI.h"
#include "UI/WaveTextUI.h"
#include "UI/BHpUI.h"
#include "UI/PlayerMindDisPlay.h"
#pragma endregion
#include "Player/Player.h"
#include "Item/PopItem.h"
#include <list>
#include "Object/Object.h"
#include "Enemy/PopEnemy.h"
#include "Back/BackGround.h"
#include "TutrialText/TutrialSystem.h"
#include "Event/ApostelEvent/ApostelEvent.h"
#include "Enemy/Frying/FryingPopEnemy.h"
#include "Animation/Effect/HitEffect.h"
#include "Pause/PouseMode.h"
#include "BGMManage/BGMManage.h"
#include "ScreenSize.h"

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

	//void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();




	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();


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
	/// 飛んでる敵の死亡
	/// </summary>
	void FryingEnemyDead();

	/// <summary>
	/// 敵が実際にポップする関数(空中飛んでるやつ)
	/// </summary>
	void FryEnemyPoping();

	/// <summary>
	/// 敵が実際にポップする奴(地上)
	/// </summary>
	/// <param name="nowWave">現在のwave</param>
	void EnemyPoping(Wave& nowWave);



	/// <summary>
	/// Wave変更関数
	/// </summary>
	void WaveChange();

	/// <summary>
	/// すべての音楽を止める奴(総括的な？)
	/// </summary>
	void AllStopMusic();

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
	/// タイトルに戻るためのフラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetFlagTitle() { return flagTitle_; };

	/// <summary>
	/// 現在のwaveを受け取る
	/// </summary>
	/// <param name="nowWave"></param>
	Wave GetNowWave() { return nowWave_; };


	/// <summary>
	/// 攻撃モーションが反応しないか
	/// </summary>
	void ChackNotAttack();

	/// <summary>
	/// 敵被弾時の向き確認用の変数()
	/// </summary>
	void ChackEToPDicrection(EnemyBase* enemy);

private:
	// シーン変更できるかどうか
	bool flagChange_ = false;
	//クリアとoverを判別するためのフラグ
	bool flagGameOver_ = false;

	//タイトルに戻る為のフラグ
	bool flagTitle_ = false;

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

	//始めるまでの時間(後で消す)
	int startFrame_ = 0;

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

	//飛んでる敵の複数化
	std::list<FryingEnemy*>fryingEnemy_;

	//敵がポップする間隔
	const int consEnemyPopFrameWave1_ = 180;
	//敵がポップする間隔
	const int consEnemyPopFrameWave2_ = 90;
	//敵がポップする間隔
	const int consEnemyPopFrameWave3_ = 120;
	//敵がポップする間隔
	const int consEnemyPopFrameBoss_ = 360;
	//敵がポップするまでを数える
	int EnemyPopFrame_ = 0;

	//敵がポップする間隔(浮遊)
	const int consEnemyPopFrameFry_ = 250;
	//敵がポップするまでを数える(浮遊)
	int fryEnemyPopFrame_ = consEnemyPopFrameFry_;



	HpUI* hpUi_ = nullptr;
	SpUI* spUi_ = nullptr;
	TimerUI* timerUi_ = nullptr;
	BackGround* backGround_ = nullptr;
	WaveTextUI* waveTextUi_ = nullptr;
	ApostelEvent* apostelEvent_ = nullptr;

	HitEffect* hitEffect_ = nullptr;
	BHpUI* bossHpUi_ = nullptr;
	
	PlayerMindDisPlay* MindUi_ = nullptr;
	

	//アイテムポップ関数
	std::list<PopItem*>popItem_;

	//waveが変わったときに入れる時間の奴
	const float timerMax = 1800.0f;

	//チュートリアルの挙動用
	TutrialSystem* tutrialSystem_ = nullptr;
	//チュートリアル用敵がいっぱい出てこないようにするため
	int countEnemy_;
	//敵が出てこなかったときに数える奴
	int enemyNotAppeared_;

	//ポーズ関連のクラスをロード
	PouseMode* pouseMode_ = nullptr;
	//BGM関連のクラスをロード
	BGMManage* bgm_ = nullptr;

	

};
