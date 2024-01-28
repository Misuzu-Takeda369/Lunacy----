#pragma once
#include "Function/UtilityStruct.h"
#include "ScreenSize.h"
#include "Function/Function.h"

class HitEffect
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 被弾した時のリアクション
	/// </summary>
	void OnColistion(EnemyType type);

	/// <summary>
	/// 揺れた分のゲッター
	/// </summary>
	/// <returns></returns>
	Vector2 GetShakePos() { return Shakepos_; };


	/// <summary>
	/// シェイク(Vector2)の関数　Update
	/// </summary>
	/// <returns></returns>
	void Update();

	void Draw();

	void SetPlayerSP(float sp);

private:

	/// <summary>
	/// 動く量
	/// </summary>
	Vector2 Shakepos_;

	/// <summary>
	/// 画面の色
	/// </summary>
	UnitColor color_;

	/// <summary>
	/// シェイクフラグ
	/// </summary>
	bool shakeFlag_;

	/// <summary>
	/// 揺らす範囲
	/// </summary>
	int randNum_ = 11;

	/// <summary>
	/// 時間図る奴
	/// </summary>
	int shakeFrame_ = 30;

	/// <summary>
	/// ダメージ属性
	/// </summary>
	EnemyType type_;

	unsigned int psychoDamageEffect_[2];
	UnitColor SPColor_;
	float playerSP_;


};

