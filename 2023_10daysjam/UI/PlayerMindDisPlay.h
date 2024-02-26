#pragma once
#include "Function/Function.h"
#include <Novice.h>

class PlayerMindDisPlay
{
public:

	void Initialize();

	void Update(MaindState& now);

	void Draw();
private:

	//現在の攻撃タイプ
	MaindState playerMindTypeNow_;

	//画像の位置
	IntState imagePos_;

	//初期位置
	IntState setPos_;

	const IntState size_ = { 64,64 };

	//画像
	int Image_;

	//画像ナンバー
	int imageNum_;


};

