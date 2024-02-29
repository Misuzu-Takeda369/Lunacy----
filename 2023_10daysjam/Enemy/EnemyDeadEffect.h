#pragma once
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/Function.h"

class EnemyDeadEffect :public Object
{

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2& pos);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// 敵が死んでいるか
	/// </summary>
	bool GetIsDead() { return isDead_; };

private:

	/// <summary>
	/// これぐらい経ったらエフェクト消えるよー目安
	/// </summary>
	const int KdeadTimer_ = 30;

	/// <summary>
	/// エフェクト起動タイマー
	/// </summary>
	int deadTimer_ = 0;

	//画像サイズ
	const IntState _spriteSize = {256,128};

	const IntState _spriteRadius = { 256/2,128/2 };

	int image_ =0;

	float _scaleX = 1.0f;
	float _scaleY = 1.0f;

	//消えるフラグ
	bool isDead_ = false;
};

