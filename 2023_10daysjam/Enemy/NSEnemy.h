#pragma once
#include "EnemyBase.h"
#include "Animation/Enemy1Anim.h"
#include "Animation/BladeSlimeAnim.h"

class NSEnemy :
    public EnemyBase
{
public:
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

private:

	const float maxHp_ = 10.0f;

	const float nomalPoint_ = 10.0f;
	float lunaticPoint_;

	//アニメーション
	//Enemy1Anim* animation_ = nullptr;
	BladeSlimeAnim* animation_ = nullptr;
};

