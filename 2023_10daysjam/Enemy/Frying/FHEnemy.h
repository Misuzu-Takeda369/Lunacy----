#pragma once
#include "Enemy/EnemyBase.h"
#include "Function/Function.h"

#include "Animation/FlyEye.h"
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

	/// <summary>
	/// 色変え合図
	/// </summary>
	/// <param name="flag">フラグ</param>
	void SetColorChange(bool flag) { ColorChange = flag; };

	///// <summary>
	///// ダメージ食らわせていいか
	///// </summary>
	///// <param name="frag"></param>
	//void SetDamageFrag(bool frag) { damageFrag_ = frag; };

	///// <summary>
	///// ここでやる
	///// </summary>
	///// <param name="state"></param>
	//void SetState(STATE state);*/

private:

	//体力の最大値
	const float maxHp_ = 10.0f;
	float Hp_;
	//コイツの火力
	const float nomalPoint_ = 25.0f;

	//縦の移動(移動の中心地)
	float center = 0.0f;
	//角度
	float theta = 0.0f;
	//グラフ？何倍か(基準が1なので)
	float ampli = 30.0f;

	//浮遊敵情報
	FlyEye* flyeye_ = nullptr;

	//攻撃合図用
	bool ColorChange = false;

	//ダメージを連続で食らわせて良いか
	bool damageFrag_ = false;

	STATE nowState_ = MOVE;

};

