#pragma once
#include "Function/Function.h"
#include <Novice.h>

class AttackTypeDisPlay
{
public:

	void Initialize();

	void Update(PlayerAttackType& now);

	void Draw();
private:

	//現在の攻撃タイプ
	PlayerAttackType playerAttackTypeNow_;

	//画像の位置
	IntState imagePos_;

	//初期位置
	IntState setPos_;

	const IntState size_ = {125,64};

	//画像
	int Image_;

	//画像ナンバー
	int imageNum_;
};

