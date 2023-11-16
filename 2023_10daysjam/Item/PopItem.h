#pragma once
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/Function.h"
#include "SpRecoverItem.h"
#include "ItemBase.h"


/// <summary>
/// アイテムポップを管理する関数
/// </summary>
class PopItem : public ItemBase 
{

public:


	enum ItemStyle {
		SpRecover,HpRecover
	};


	~PopItem();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2& pos);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// 当たった時の挙動
	/// </summary>
	void OnColistion() override;



	SpRecoverItem* GetSpRecoverItem() { return spRecoverItem_; };

	/// <summary>
	/// 当たり判定の時に引用するよう変数
	/// </summary>
	/// <returns></returns>
	float  GetRecoverState() { return recoverState_; };

private:

	int run_;
	ItemStyle popItem_;

	//Sp回復フラグ
	SpRecoverItem* spRecoverItem_ = nullptr;

	//当たり判定の時に引用するよう変数
	float recoverState_ = 0.0f;


};

