#pragma once
#include "Object/Object.h"
#include <list>

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

	/// <summary>
	/// 被弾した時に動く奴
	/// </summary>
	/// <param name="damege"></param>
	virtual void OnCollision(float& damege) override;

	/// <summary>
	/// 被弾した時に後ろに下がる挙動
	/// </summary>
	/// <param name="m">移動量</param>
	virtual void OncollBackMove(float m);

	/// <summary>
	/// 被弾時のエフェクト(死んだときの状態) 
	/// </summary>
	virtual void OncollEffect();

	/// <summary>
	/// 敵の死亡モーション(共通にしようかねぇと)
	/// </summary>
	virtual void DeadEnemyEffect();

	/// <summary>
	/// エフェクトの追加(死亡時の奴)
	/// </summary>
	virtual void AddDeadEffect(const Vector2& pos);

	//敵が死んでいるか
	virtual bool GetIsDead() { return isDead_; };

	virtual void SetDirection(bool right)
	{
		_right =right;
	};


	/// <summary>
	 /// 攻撃
	 /// </summary>
	virtual void AttackMotion();

	/// <summary>
	/// 攻撃のモーション状態
	/// </summary>
	virtual void AttackCool();

	/// <summary>
	/// 向きによってバックさせる向きを変更するため
	/// </summary>
	/// <param name="Bm"></param>
	void SetBaseMoveX(float Bm) { BaseMoveX_ = Bm; };

	/// <summary>
	/// 移動量定数
	/// </summary>
	/// <returns></returns>
	float GetkBaseMoveX_() { return kBaseMoveX_; };


protected:


	//敵が死んでいるか
	bool isDead_;

	//敵が移動した量
	Vector2 moveEnemy_;

	//被弾のクールタイム
	int hitCoolTime_ = 0;
	const int MaxHitCoolTime_ = 10;

	bool _right;

	//被弾した時に下がる最大量(基準)
	const float kBaseMoveX_ = 1.5f;

	//判別用(向きによって変わる為)
	float BaseMoveX_ = kBaseMoveX_;

	//どれぐらい下がったか確認用
	float MoveX_ = 0.0f;

	//スピード定数
	const float kBackSpeedX_ = 0.5f;

	//スピード定数(向き適応版)
	float BackSpeedX_ = kBackSpeedX_;

	//敵の消滅モーション
	bool deadEffect_ = false;

	///多分球が出てくるまでの時間?
	int _deadEffectPopTimer = 0;

	/// <summary>
	/// 消滅させる時間
	/// </summary>
	int _deadEffectStopTimer = 0;

	/// <summary>
	/// 消滅させる時間最大チ
	/// </summary>
	const int _DeadEffectStopTimerMax = 10;
};

