#pragma once
#include <Vector2.h>
#include <ScreenSize.h>
#include <Novice.h>
#include "ImGuiManager.h"
#include "Function/UtilityStruct.h"


class EHpUI
{
public:

	//~HpUI();

	/// <summary>
	/// 初期化(没)
	/// </summary>
	//void Initialize(Vector2 pos, int moveSpeedX);

	/// <summary>
	/// 初期化(数字表示)
	/// </summary>
	/// <param name="pos">敵の位置</param>
	/// <param name="Hp">体力</param>
	void Initialize(Vector2 pos,float Hp);

	/// <summary>
	/// 毎フレーム処理(没)
	/// </summary>
	//void Update(float decreasedHp, Vector2 pos);

	/// <summary>
	/// 更新(新)
	/// </summary>
	/// <param name="Hp">現在のHP</param>
	/// <param name="pos">現在の位置</param>
	void Update(float Hp, Vector2 pos);

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 敵のHpを画像に変換する関数
	/// </summary>
	void EnemyHpToImageNum();

private:

	//左端
	IntState Lpos_ = { 0,0 };
	//右端
	IntState Rpos_ = { 0,0 };
	//画像
	int image_ = Novice::LoadTexture("./Resources/images/number/NumMini.png");
	
	//int frameImage_ = 0;
	//写したいサイズ
	const int sizeX_ = 35;
	const int sizeY_ = 56;

	//移動した合計
	int moveX_ = 0;
	//移動する量(HPが1減るたびに動く量)
	int moveSpeedX_ = 5;

	//Hp
	int nowHp_;
	//画像に写るよう
	int HpDigitDraw_[3];

	//画像の列
	int numX_[3] = {0,0,0};
	//画像の行
	int numY_[3] = { 0,0,0 };

};

