#pragma once
#include "Object/Object.h"
//時限爆弾をプレイヤーの現在位置(横)に向かって投げる/爆破する
class Apostel_ThrowMine :public Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(CharaBase owner, Vector2 playerPos);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw()override;

	bool IsDead() { return isDead_; }

	bool GetDirection() {
		if (moveDirection_ < 0)
			return false;
		return true;
	}
	/// <summary>
	/// ダメージ量取得 
	/// </summary>
	/// <returns></returns>
	float GetAttackPoint() override {
		if (isActive_)
			return attackPoint_;
		return 0;
	}
	bool GetIsActive() {
		return isActive_;
	}
	EnemyType GetAttributeType() { return (EnemyType)attribute_; };

private:

	bool isDead_ = false;
	MaindState attribute_ = Normal;
	float fallSpeed_ = 0;
	Vector2 target_;
	Vector2 start_;
	const float baseRadius_ = 10.f;
	int moveDirection_ = 1;
	float attackPoint_ = 30.f;
	float t_ = 0;
	bool isActive_ = false;
	int timeCounter_; //時間カウント
	const int baseActiveTime_ = 60; //アクティブにするまでの時間
	const float maxRadius_ = 90.f;//最大爆発衝突範囲
	float groundLevel_ = 614.f; //地面の位置
	int blinkingTimer_ = 0;
	bool blinking_ = true;

	///音源
	//時限爆弾爆発
	int timeBombExplosionEffect_ = 0;
	//時限爆弾爆発
	int timeBombExplosionPlay_ = 0;

	int sprite_;
	float theta_ = 0;
	float rotateSpeed_ = 0;
	unsigned int effect_;
	bool effectFlag_ = false; bool effectScaleFlag_ = false;
	float effectTheta_ = 0;
	float effectScale_ = 0;
	float effectScaleSpeed_ = 0;
};

/*
 ***衝突判定***

	for (Apostel_ThrowMine* mine : apostelEvent_->GetThrowMine()) {
		if (mine->GetIsActive()) {
			if (IsCollision(mine, player_) == true) {

				float damage = mine->GetAttackPoint();
				EnemyType enemytype = mine->GetAttributeType();
				player_->OnCollision(damage, enemytype);
			}
		}

	}
*/