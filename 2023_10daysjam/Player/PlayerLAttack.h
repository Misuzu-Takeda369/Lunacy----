#pragma once
#include "Object/Object.h"

class PlayerLAttack : public Object
{
public:
	/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="playerAttackTypeNow">攻撃のtype</param>
		/// <param name="maindStateNow">現在狂気か否か</param>
		/// <param name="playerDirection">向き</param>
	void Initialize(PlayerAttackType& playerAttackTypeNow, MaindState& maindStateNow, PlayerDirection& playerDirection, Vector2& playerPos);
	

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw() override;


	/// <summary>
	/// クラスの外部用弾消えるためのフラグ変数
	/// </summary>
	bool IsDead() const { return isDead_; };

	/// <summary>
	/// 攻撃力を決める関数
	/// </summary>
	void DeterminingAttackPower(float hp, float maxHp);

	/// <summary>
	/// 攻撃力受け取り
	/// </summary>
	/// <returns></returns>
	float GetAttackPoint() { return attackPoint_; };

	/// <summary>
	/// 当たった時の挙動
	/// </summary>
	void OnCollision();

private:


	///プレイヤーから引っ張ってくる引数
	//現在の攻撃type
	PlayerAttackType playerAttackTypeNow_;
	//プレイヤーの向き
	PlayerDirection playerDirection_;

	//弾の寿命(消えるまでの時間の定数)
	static const int kLifeTime = 120;
	// 弾の寿命(消えるまでの時間の判定用変数)
	int deathTimer_ = kLifeTime;
	//消えるフラグ
	bool isDead_ = false;

	//最終的に判断する攻撃力
	float attackPoint_ = 0.0f;
	//計算時の倍率
	const float attackMultiples_ = 0.02f;

	//攻撃力(magic時　変動あり)
	float magicAttackPoint_ = 5.0f;

};

