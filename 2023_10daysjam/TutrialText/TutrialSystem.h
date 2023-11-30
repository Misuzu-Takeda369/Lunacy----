#pragma once
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/Function.h"
#include "TutrialText.h"
//#define TEXT_MAX 12

class TutrialSystem
{
public:

	enum TutrialAction {
		//移動の説明,攻撃(通常),チェンジ,魔法攻撃,狂気モード,フリー,ジャンプ
		Move,AttackNomal,AttackChange ,AttackMagic,LunaMode,Free, Junp
	};

	//デストラクタ
	~TutrialSystem();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(float Pspeedx);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(MaindState Pmaind, PlayerAttackType Patteck);

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 敵のスポーン関連等の為のモノ(適応めんどいのでintに変換)
	/// </summary>
	/// <returns></returns>
	int GetNowExprestion() { return (int)nowExprestion_; };

	/// <summary>
	/// 現在の説明セッターsetter
	/// </summary>
	/// <returns></returns>
	void SetNowExprestion(int nowexpresstion) {  nowExprestion_ = (TutrialAction)nowexpresstion; };

	/// <summary>
	/// チュートリアル終了処理
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() {
		return IsDead_;
	};

private:

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//テキスト関連
	TutrialText* tutrialtext_ = nullptr;

	//現在説明すべきモノ
	TutrialAction nowExprestion_ = Move;

	///Move
	//移動した距離
	float moveDestance_ = 0.0f;
	//プレイヤーのスピード
	float playerSpeed_ = 0.0f;

	//ボタンを推し続けた時間
	int pushBotton_ = 0;
	///Junp
	int jumpCount_ = 0;

	///AttackChange
	//何回精神状態変えたか
	int countchange_ = 0;
	//現在のプレイヤーの状態
	MaindState nowPMaind_ = Normal;
	//現在のプレイヤーの攻撃モード
	PlayerAttackType nowPattack_ = Plane;

	///free
	bool IsDead_ = false;

	//テキストの現在のnum
	int imageNum_;

	int frameCool_ = 0;
	const int frameCoolMAX_ = 60;
};

