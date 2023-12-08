#pragma once
#include "Enemy/EnemyBase.h"
#include <list>
#include "Animation/ApostelAnim.h"
#include "UI/EHpUI.h"
#include "Apostel_MagicBall.h"
#include "Apostel_ThrowMine.h"
class Apostel :public EnemyBase

{
public:
	~Apostel();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, Vector2 speed, float radius)override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// 敵の移動処理
	/// </summary>
	void Move()override;

	/// <summary>
	/// 自然に消えるパターン
	/// </summary>
	void NaturalDeath()override;

	void OnCollision(float& damege) override;

	void SetPlayerBase(CharaBase player);

	//敵が死んでいるか
	virtual bool GetIsDead() { return isDead_; };

	virtual void SetDirection(bool right)
	{
		_right = right;
	};
	int GetPhase() { return phase_; }

	const std::list<Apostel_MagicBall*>& GetMagicBall() { return magicBall_; }
	const std::list<Apostel_ThrowMine*>& GetThrowMine() { return throwMine_; }

protected:

	void Phase_First();
	void Phase_Second();
	void Phase_Third();
	void CoolCheak() override;
	//発射体(本体と分離した攻撃)の処理をまとめて行う
	void DrawProjectile();
	void UpdateProjectile();
	void DeleteProjectile();
	void MagicBallFire();
	void ThrowMineFire();
	//敵が死んでいるか
	bool isDead_;

	//敵が移動した量
	Vector2 moveEnemy_;

	//被弾のクールタイム
	int hitCoolTime_ = 0;
	const int MaxHitCoolTime_ = 5;

	bool _right; //アニメーションに渡すようの向き
	const float maxHP_ = 100;

	STATE state_ = IDOL;
	SABSTATE sabState_ = SABSTATE::_NONE;

	enum Phase {
		dead, //0 
		first, //1
		second, //2
		third, //3
	};
	Phase phase_ = first;

	int actChangeTime_ = 0; //行動変更時間
	ApostelAnim* anim_ = nullptr; 
	CharaBase playerBase_;
	EHpUI* hpUI_;
	int moveDirection_ = 1; //向き
	int magicBallCoolTimeCounter_ = 0;
	int magicBallCoolTime_ = 60;
	int throwMineCoolTimeCounter_ = 0;
	int throwMineCoolTime_ = 30;
	float flowingTheta_ = 0;
	Vector2 center_;
	UnitColor color_;

	std::list<Apostel_MagicBall*> magicBall_;
	std::list<Apostel_ThrowMine*> throwMine_;
};

