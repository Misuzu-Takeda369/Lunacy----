﻿#pragma once
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
	void Initialize(MaindState maindStateNow);

	void Initialize(MaindState maindStateNow,Wave nowWave);

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

};

