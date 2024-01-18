#pragma once

#include "Object/Object.h"
#include <list>
#include "Function/Function.h"
#include "PlayerMAttack.h"
#include "PlayerLAttack.h"
#include "Animation/PlayerAnimation.h"
#include "PlayerJewel.h"



class Player : public Object
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(char* keys, char* preKeys);

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw() override;

	void Draw(Vector2 ShakePos);

	/// <summary>
	/// キー入力
	/// </summary>
	void Move(char* keys, char* preKeys);
	/// <summary>
	///	ジャンプ処理用
	/// </summary>
	void Jump();

	/// <summary>
	/// 攻撃のtypeが変わる
	/// </summary>
	void AttackTypeChange();

	/// <summary>
	/// 精神状態の変更(基底クラスに移動挙動すべて一緒のはずなので)
	/// </summary>
	void MindTypeChange();

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();

	/// <summary>
	/// 弾が消える関数
	/// </summary>
	void BulletDead();

	/// <summary>
	/// 攻撃時のSPの処理
	/// </summary>
	void AttackSpDown();

	/// <summary>
	/// プレイヤーの攻撃方向をマウスの位置で決める
	/// </summary>
	void playerDirectionDecisionA();


	/// <summary>
	/// enum　State適応のチェンジ
	/// </summary>
	void PlayerStateChange(char* keys);

	/// <summary>
	/// 当たった時の挙動
	/// </summary>
	void OnCollision(float& damage, EnemyType& enemytype);

	/// <summary>
	/// 連続ダメージ
	/// </summary>
	/// <param name="damage">ダメージ</param>
	/// <param name="timer">チェックタイマー</param>
	/// <param name="flag">やっていいか否か</param>
	void OnContinuousDamage(float& damage,int& timer,bool& flag);

	/// <summary>
	/// 当たった時の挙動
	/// </summary>
	void UsedItem(float& recover);

	/// <summary>
	/// クールタイムか否か
	/// </summary>
	void CoolCheak() override;

	/// <summary>
	/// アイテムを連続でゲットしないよう？
	/// </summary>
	void ItemCoolCheak();

	bool GetAttackFrag() { return attackFrag_; };

	/// <summary>
	/// UIに投げるよう
	/// </summary>
	/// <returns></returns>
	float GetSpChangingPoint() { return spChangingPoint_; };


	/// <summary>
	/// 近距離の攻撃のゲッター
	/// </summary>
	/// <returns></returns>
	PlayerMAttack* GetMAttack() { return mAttack_; };

	/// <summary>
	/// 遠距離の攻撃のゲッター
	/// </summary>
	/// <returns></returns>
	const std::list<PlayerLAttack*>& GetBullet() { return lAttack_; };

	/// <summary>
	/// チュートリアルに引っ張る用のプレイヤースピード
	/// </summary>
	/// <returns></returns>
	float GetPlayerSpeedX() { return charaBase_.speed_.x; };

	/// <summary>
	/// 攻撃タイプ判別
	/// </summary>
	/// <returns></returns>
	PlayerAttackType GetPlayerAttackTypeNow() { return playerAttackTypeNow_; };

	/// <summary>
	/// チュートリアル用ゲージ管理
	/// </summary>
	/// <param name="spPoint"></param>
	/// <returns></returns>
	void SetSpChangingPoint(float spPoint) { spChangingPoint_ = spPoint; };

	/// <summary>
	/// 曲を止めるよう
	/// </summary>
	void StopMusic()override;


private:

	//マウスの位置(Yも無いと関数動かん)
	IntState mousePos_ = { 0,0 };

	//STATE用変数
	STATE playerState_ = IDOL;
	SABSTATE sabState_ = _NONE;

	//プレイヤーの向き(攻撃の向き)
	PlayerDirection playerDirectionA_ = RIGHT;

	//プレイヤーの向き(動き(待機や移動などキー入力で変化するタイプ))
	PlayerDirection playerDirectionM_ = RIGHT;

	//精神状態が変わる値の変数(koko)
	float spChangingPoint_ = 250.0f;
	//magic攻撃時のSP減少量
	float attackSpDown_ = 50.0f;

	//近距離用の当たり判定用クラス
	PlayerMAttack* mAttack_ = nullptr;

	//遠距離の当たり判定(複数にする)
	std::list<PlayerLAttack*> lAttack_;

	//アニメーション関連
	PlayerAnimation* playerAnimation_ = nullptr;

	//プレイヤーの攻撃モードが分かる奴
	PlayerJewel* jewel_ = nullptr;

	///ジャンプ関連
	//ジャンプの最初のスピード
	float jumpSpeed_;
	//ジャンプするかのフラグ
	bool jumpFrag_ = false;
	//ジャンプのラグ
	//int jumpLag_ = 0;
	///ジャンプ関連
	const float baseJumpSpeed_ = 35.f;

	///攻撃関連
	//現在の攻撃type
	PlayerAttackType playerAttackTypeNow_ = Plane;
	//近距離攻撃できるかフラグ(近距離)
	bool attackFrag_ = false;


	//最初にいる位置
	Vector2 standardPos_;

	//攻撃している時間仮近距離(多分eff・animeでいらなくなる)
	int attackframe_ = 30;
	const int baseAttackFrame_ = 10;

	//アイテムを取得中か
	bool getItem_ = false;
	//取得フレーム関連
	int getCoolTime_ = 0;
	const int MaxGetCoolTime_ = 10;

	//狂気時の被弾倍率
	const float hitMagnification_ = 0.2f;

	///音響関連
	//音(本体) 
	int attackNomalEffect_ = 0;
	//音(本体) 
	int attackMacgiEffect_ = 0;
	//音(本体) 
	int walkEffect_ = 0;
	//音(本体) 
	int jumpEffect_ = 0;
	//音(本体) 
	int hitHpEffect_ = 0;
	//音(本体) 
	int hitSpEffect_ = 0;
	//音(本体) 
	int usedItemEffect_ = 0;

	//ハンドル
	int attackNomalPlay_ = 0;
	//ハンドル
	int attackMacgiPlay_ = 0;
	//ハンドル
	int walkPlay_ = 0;
	//ハンドル
	int jumpPlay_ = 0;
	//ハンドル
	int hitHpPlay_ = 0;
	//ハンドル
	int hitSpPlay_ = 0;
	//ハンドル
	int usedItemPlay_ = 0;

};