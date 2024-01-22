#pragma once
#include "Enemy/EnemyBase.h"
#include "Object/Object.h"
#include "Function/Function.h"
#include "UI/EHpUI.h"
#include "Enemy/Frying/FHEnemy.h"

/// <summary>
/// 浮遊する敵
/// </summary>
class FryingEnemy :public EnemyBase
{
public:
	~FryingEnemy();

	void Initialize(MaindState maindStateNow, int enemyNotAppeared);

	void Update() override;
	void Draw() override;

	void OnCollision(float& damege);


	/// <summary>
	/// 敵の生成(敵の種類やタイプをここで判断)
	/// </summary>
	void EnemyBorn();

	/// <summary>
	/// クールタイムか否か
	/// </summary>
	void CoolCheak() override;


	/// <summary>
	/// 当たり判定用に使う敵のタイプ
	/// </summary>
	/// <returns></returns>
	EnemyType GetEnemyType() { return enemyType_; };

	/// <summary>
	/// 敵が出てきていない回数
	/// </summary>
	/// <param name="num">回数</param>
	int EnemyNotAppeared() { return enemyNotAppeared_; }

	/// <summary>
	/// ダメージまでの時間
	/// </summary>
	/// <returns></returns>
	int GetDamageLimitTime() { return damageLimitTime_; };

	/// <summary>
	/// 連続でダメージ食らわせていいか
	/// </summary>
	/// <returns></returns>
	bool GetDamageFrag() { return damageFrag_; };

	/// <summary>
	/// 連続ダメージ関連の関数
	/// </summary>
	void ContinuousDamage();

	/// <summary>
	/// 連続ダメージの値(もしなんか増えても統一)
	/// </summary>
	/// <returns></returns>
	float GetContinuousDamage() { return continuousDamage_; };

	///// <summary>
	// /// 攻撃
	// /// </summary>
	//void AttackMotion();

	///// <summary>
	///// 攻撃のモーション状態
	///// </summary>
	//void AttackCool() override;

private:

	//通常時の浮遊
	FHEnemy* fhEnemy_ = nullptr;

	//現在出ている敵の数(ENEMY_MAXになると減るまで敵がでなくなる)
	int countEnemy_ = 0;

	//乱数用の数
	int rumNum_ = 0;
	//敵の種類用
	EnemyType enemyType_ = NONE;

	//Hpゲージ用
	EHpUI* eHUi_ = nullptr;

	float maxHp_;

	//敵が出てこなかったときに数える奴
	int enemyNotAppeared_;

	//音関連
	int hitEffect_ = 0;
	int alarmEffect_ = 0;
	//ハンドル
	int hitPlay_ = 0;
	int alarmPlay_ = 0;

	//制限時間(最初)
	const int damageLimitTimeFMax_ = 500;
	//制限時間(2回目以降)
	const int damageLimitTimeMax_ = 180;
	//制限時間(ダメージ食らうまで)
	int damageLimitTime_ = 0;

	//ダメージを連続で食らわせて良いか
	bool damageFrag_ = false;

	//ダメージ
	const float continuousDamage_ = 5.0f;


	bool attackFrag_ = false;

	int attacktimer_ = 0;
};

