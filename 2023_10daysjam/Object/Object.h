#pragma once
#include <Vector2.h>
#include <Novice.h>
#include "ImGuiManager.h"
#include "CharaBase.h"

class Object
{

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update(char* keys, char* preKeys);

	/// <summary>
	/// 前景描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 当たった時の挙動
	/// </summary>
	virtual void OnCollision(float& damege);

	/// <summary>
	/// クールタイムか否か
	/// </summary>
	virtual void CoolCheak();

	/// <summary>
	/// 現在のHP
	/// </summary>
	/// <returns></returns>
	virtual float GetHp() { return hp_; };
	/// <summary>
	/// 現在のSP
	/// </summary>
	/// <returns></returns>
	virtual float GetSp() { return sp_; };

	/// <summary>
	/// 当たり判定に使う用のゲッターX
	/// </summary>
	/// <returns></returns>
	virtual float GetPosX() { return charaBase_.pos_.x; };
	/// <summary>
	/// 当たり判定に使う用のゲッターY
	/// </summary>
	/// <returns></returns>
	virtual float GetPosY() { return charaBase_.pos_.y; };
	/// <summary>
	/// 当たり判定に使う用のゲッター半径
	/// </summary>
	/// <returns></returns>
	virtual float GetRadish() { return charaBase_.radius_; };

	/// <summary>
	/// 攻撃力受け取り
	/// </summary>
	/// <returns></returns>
	virtual float GetAttackPoint() { return attackPoint_; };

	virtual  CollisionType GetCollisionType() { return collisionType_; }

	virtual Vector2 GetBoxSize() { return boxSize_; }
	virtual CharaBase GetCharaBase() { return charaBase_; }

	virtual MaindState GetMaindStateNow() { return maindStateNow_; };

protected:

	//基準となる情報(ここからアニメーション用に引っ張る)
	CharaBase charaBase_;

	float hp_;
	float sp_;

	//現在の狂気度
	MaindState maindStateNow_ = Normal;
	//狂気カラー(デバック用)
	unsigned int maindColor_ = WHITE;

	//最終的に判断する攻撃力
	float attackPoint_ = 0.0f;

	CollisionType collisionType_ = None;
	Vector2 boxSize_;

	//攻撃をされている
	bool hit_ = false;
	//被弾のクールタイム
	int hitCoolTime_ = 0;
	const int MaxHitCoolTime_ = 120;


};

