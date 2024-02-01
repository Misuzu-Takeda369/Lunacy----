#pragma once
#include "EnemyBullet.h"
#include "Object/Object.h"
#include "NHEnemy.h"
#include "NSEnemy.h"
#include "Function/Function.h"
#include "EnemyBase.h"
//ここに敵のUIを搭載(シーンの方だとめんどいことになるので)
#include "UI/EHpUI.h"
#define ENEMY_MAX 10

//敵クラス(総括クラスポップ用に変更)
class PopEnemy :public EnemyBase
{
public:


	~PopEnemy();

	//後から場所だけ敵から受け取る
	//void Initialize(MaindState maindStateNow);

	void Initialize(MaindState maindStateNow,Wave nowWave, int enemyNotAppeared);

	void Update() override;
	void Draw() override;

	void OnCollision(float& damege);


	/// <summary>
	/// 敵の生成(敵の種類やタイプをここで判断)
	/// </summary>
	/// <param name="nowWave">現在のwave</param>
	void EnemyBorn(Wave nowWave);

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
	 int EnemyNotAppeared() {return enemyNotAppeared_;}

	 /// <summary>
	 /// シーン変換の時に音を止める関数
	 /// </summary>
	 void StopMusic() override;

	 /// <summary>
	 /// 攻撃
	 /// </summary>
	 void AttackMotion();

	 /// <summary>
	 /// 攻撃のモーション状態
	 /// </summary>
	 void AttackCool();


	 void DeadEnemyEffect();

private:

	//通常の敵
	NHEnemy* nHEnemy_ = nullptr;
	NSEnemy* nSEnemy_ = nullptr;

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

	///音響関連
	//音関連
	int hitEffect_ = 0;
	int walkEffect_ = 0;
	//ハンドル
	int hitPlay_ = 0;
	int walkPlay_ = 0;

	Wave nowWave_ = Tutorial;

	bool attackFrag_ = false;
	
	int attacktimer_ = 0;
};

