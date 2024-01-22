#pragma once
#include "EnemyBase.h"
//#include "Animation/Enemy1Anim.h"
#include "Animation/BladeSlimeAnimH.h"

class NHEnemy :public EnemyBase
{
public:

	~NHEnemy();
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

	void SetState(STATE state);
	
private:

	//体力の最大値
	const float maxHp_ = 10.0f;

	//コイツの火力
	const float nomalPoint_ = 50.0f;

	//アニメーション
	//Enemy1Anim* animation_ = nullptr;
	BladeSlimeAnim* animation_ = nullptr;

	

};

