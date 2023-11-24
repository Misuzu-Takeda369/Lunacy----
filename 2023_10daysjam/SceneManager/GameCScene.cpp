#include "SceneManager/GameCScene.h"


GameCScene::GameCScene() {}

GameCScene::~GameCScene() {}

void GameCScene::Initialize()
{
	gameClearImage_ = Novice::LoadTexture("./Resources/images/Text/GameClear.png");
	toTitleImage_ = Novice::LoadTexture("./Resources/images/Text/clickTitle.png");

	toTitlePos_  = { 450,400 };

	toTitleColor_ = { 255,255,255,255,0xFFFFFFFF };

	
}

void GameCScene::Update()
{

	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	//ここのif文でシーン移行出来るかを判別
	changeTimingFrame_++;

	MouseBottonChack();

#ifdef _DEBUG
	//ここのif文でシーン移行出来るかを判別
	//現在は1を押したときに移動
	if ((preKeys[DIK_I] == 0 && keys[DIK_I] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
			flagChange_ = true;
			changeTimingFrame_ = 0;
	}
#endif // _DEBUG

}

void GameCScene::Draw() 
{
	//背景‽の色
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x30182CFF, kFillModeSolid);
	//タイトル
	Novice::DrawSprite(250, 50, gameClearImage_, 1.0f, 1.0f, 0.0f, WHITE);

	//文字の奴
	Novice::DrawSprite(toTitlePos_.x_, toTitlePos_.y_, toTitleImage_, 1.0f, 1.0f, 0.0f, toTitleColor_.color);

}

void GameCScene::MouseBottonChack()
{
	//範囲に入っている場合に入っている場合左クリックするとスターとする
	if (Novice::IsTriggerMouse(0)&& changeTimingFrame_ >= changeTimingFrameMax_) {
		flagChange_ = true;
		changeTimingFrame_ = 0;
	}
}

