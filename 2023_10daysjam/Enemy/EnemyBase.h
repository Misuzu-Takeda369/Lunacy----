#pragma once
#include "Object/Object.h"

class EnemyBase : public Object
{

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(Vector2 pos, Vector2 speed, float radius);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	virtual void Draw()override;

	/// <summary>
	/// 敵の移動処理
	/// </summary>
	virtual void Move();

	/// <summary>
	/// 自然に消えるパターン
	/// </summary>
	virtual void NaturalDeath();

	virtual void OnCollision(float& damege) override;

	//敵が死んでいるか
	virtual bool GetIsDead() { return isDead_; };

	virtual void SetDirection(bool right)
	{
		_right =right;
	};

protected:


	//敵が死んでいるか
	bool isDead_;

	//敵が移動した量
	Vector2 moveEnemy_;

	//被弾のクールタイム
	int hitCoolTime_ = 0;
	const int MaxHitCoolTime_ = 10;

	bool _right;
};

