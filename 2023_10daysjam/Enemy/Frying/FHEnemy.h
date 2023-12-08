#pragma once
#include "Enemy/EnemyBase.h"
#include "Function/Function.h"
class FHEnemy :public EnemyBase
{
public:

	~FHEnemy();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, Vector2 speed, float radius) override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 最大値のHP
	/// </summary>
	/// <returns></returns>
	float GetHpMax() { return maxHp_; };

	/// <summary>
	/// 移動処理を精神毎に分けたい(願望)
	/// </summary>
	void Move()override;

private:

	//体力の最大値
	const float maxHp_ = 10.0f;

	//コイツの火力
	const float nomalPoint_ = 50.0f;

	//縦の移動(移動の中心地)
	float center = 0.0f;
	//角度
	float theta = 0.0f;
	//グラフ？何倍か(基準が1なので)
	float ampli = 30.0f;

};

