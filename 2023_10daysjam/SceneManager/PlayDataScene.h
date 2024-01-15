#pragma once
#include "SaveData.h"
#include "Function/UtilityStruct.h"
#include <Novice.h>
class PlayDataScene
{
public:
	void Initialize();
	void Update();
	void SetSaveData(SaveData* data);
	void Draw();
	void SetSceneChangeFlag(bool flag) { backTitleFlag = flag; }
	bool GetSceneChangeFlag() { return backTitleFlag; }
	void SetTips(int num) { 
		int a = num;
		if (num >= maxTips_) {
			a = maxTips_ - 1;
		}
		tipsNum_ = a; }
	int GetMaxTips() { return maxTips_; }
private:
	void MouseBottonChack();
	SaveData* data_;

	IntState mousePos_ = { 0,0 };
	bool backTitleFlag = false;
	unsigned int backTitleButton_;
	IntState backButtonPos_ = { 40,550 };
	int buttonSize_ = int(512 * 0.25);
	int time_[6];
	int timeNum_;

	int numSprite[10] = { 
		Novice::LoadTexture("./Resources/images/number/0.png"),
		Novice::LoadTexture("./Resources/images/number/1.png"),
		Novice::LoadTexture("./Resources/images/number/2.png") ,
		Novice::LoadTexture("./Resources/images/number/3.png") ,
		Novice::LoadTexture("./Resources/images/number/4.png") ,
		Novice::LoadTexture("./Resources/images/number/5.png") ,
		Novice::LoadTexture("./Resources/images/number/6.png") ,
		Novice::LoadTexture("./Resources/images/number/7.png"),
		Novice::LoadTexture("./Resources/images/number/8.png"),
		Novice::LoadTexture("./Resources/images/number/9.png") };
	unsigned int koron_;
	unsigned int datawall1_;
	unsigned int dataText1_;
	unsigned int commentBack_;
	static const int maxTips_ = 3;
	int tips_[maxTips_] = {
		Novice::LoadTexture("./Resources/images/Text/tips1.png"),
		Novice::LoadTexture("./Resources/images/Text/tips2.png"),
		Novice::LoadTexture("./Resources/images/Text/tips3.png")
	};
	int tipsNum_ = 0;

	//画像を少しデカくしたらおもろそう
	float ScaleSizeX = 0.25f;
	float ScaleSizeY = 0.25f;

	///音関連(リソース) 
	int selectEffect_ = 0;
	int decisionEffect_ = 0;

	//音の尺が短すぎて機能してない(意味ない)かも
	int selectEffectPlay_ = 0;
	bool OnselectBackPlay_ = false;

};

//要るかどうかというと別に…(・∀・)