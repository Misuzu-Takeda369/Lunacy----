#pragma once
#include "Object/Object.h"

class ItemBase :public Object
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	virtual void Draw()override;


	/// <summary>
	/// クラスの外部用アイテム消えるためのフラグ変数
	/// </summary>
	bool IsDead() const { return isDead_; };

	/// <summary>
	/// 当たった時の挙動
	/// </summary>
	virtual void OnColistion();

protected:

	//画像サイズ
	int sizeX_; int sizeY_;
	int image_;

	//弾の寿命(消えるまでの時間の定数)
	static const int kLifeTime = 360;
	// 弾の寿命(消えるまでの時間の判定用変数)
	int deathTimer_ = kLifeTime;
	//消えるフラグ
	bool isDead_ = false;
};

