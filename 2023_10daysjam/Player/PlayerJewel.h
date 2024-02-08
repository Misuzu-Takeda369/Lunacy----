#pragma once
#include "Novice.h"
#include "CharaBase.h"
#include"UI/AttackTypeDisPlay.h"

//攻撃typeを視認的に分かるようにするためのクラス
class PlayerJewel
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerJewel();
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(unsigned int& color);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Vector2& pos, PlayerAttackType& playerAttackType, PlayerDirection& playerDurection);

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

private:

	//写る場所
	CharaBase jewelstate_;

	//画像サイズ
	const IntState imageSize_ = {32,32};


	//プレイヤーからの距離
	const IntState playerDistance_ = {64,32 };

	//上の表示用クラス
	AttackTypeDisPlay* atdp_ = nullptr;
};

