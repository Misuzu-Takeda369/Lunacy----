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
	//ハンドル
	int hitPlay_ = 0;

};

