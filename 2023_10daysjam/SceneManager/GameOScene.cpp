#include "GameOScene.h"

GameOScene::GameOScene() {}

GameOScene::~GameOScene() {}


void GameOScene::Initialize() 
{
	gameOverImage_ = Novice::LoadTexture("./Resources/images/Text/GameOver.png");
	retryImage_ = Novice::LoadTexture("./Resources/images/Text/Retry.png"); 
	toTitleImage_ = Novice::LoadTexture("./Resources/images/Text/toTitle.png");


	retryPos_ = { 450,350 };
	toTitlePos_ = { 450,550 };

	mousePos_ = { 0,0 };
	retryColor_ = { 255,255,255,255,0xFFFFFFFF };
	toTitleColor_ = { 255,255,255,255,0xFFFFFFFF };

}

void GameOScene::Update()
{

	memcpy(preKeys, preKeys, 256);
	Novice::GetHitKeyStateAll(keys);
#pragma region シーン変換
	
	changeTimingFrame_++;
	//マウスでのシーン変更
	MouseBottonChack();

#ifdef _DEBUG

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動タイトルへ
	if ((preKeys[DIK_I] == 0 && keys[DIK_I] != 0) && changeTimingFrame_ >= 60) {
		flagChange_ = true;
		changeTimingFrame_ = 0;
	}
	//リトライする場合
	else if ((preKeys[DIK_O] == 0 && keys[DIK_O] != 0) && changeTimingFrame_ >= 60) {
		flagChange_ = true;
		flagRetry_ = true;
		changeTimingFrame_ = 0;
	}

#endif // _DEBUG

#pragma endregion
}

void GameOScene::Draw() 
{
	//背景‽の色
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x30182CFF, kFillModeSolid);
	//タイトル
	Novice::DrawSprite(250, 50, gameOverImage_, 1.0f, 1.0f, 0.0f, WHITE);

	//文字の奴
	Novice::DrawSprite(retryPos_.x_, retryPos_.y_, retryImage_, 1.0f, 1.0f, 0.0f, retryColor_.color);
	Novice::DrawSprite(toTitlePos_.x_, toTitlePos_.y_, toTitleImage_, 1.0f, 1.0f, 0.0f, toTitleColor_.color);

}

void GameOScene::MouseBottonChack()
{
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);


#pragma region リトライの方
	if ((mousePos_.x_ >= retryPos_.x_ && mousePos_.x_ <= retryPos_.x_ + textSizeX_)
		&&
		(mousePos_.y_ >= retryPos_.y_ && mousePos_.y_ <= retryPos_.y_ + textSizeY_))
	{
		retryColor_.color = RED;
		//範囲に入っている場合に入っている場合左クリックするとスターとする
		if (Novice::IsTriggerMouse(0)) {
			flagChange_ = true;
			flagRetry_ = true;
			
		}
	}
	else {
		retryColor_.color = WHITE;
	}
#pragma endregion

#pragma region タイトルに戻る方
	if ((mousePos_.x_ >= toTitlePos_.x_ && mousePos_.x_ <= toTitlePos_.x_ + textSizeX_)
		&&
		(mousePos_.y_ >= toTitlePos_.y_ && mousePos_.y_ <= toTitlePos_.y_ + textSizeY_))
	{
		toTitleColor_.color = RED;
		//範囲に入っている場合に入っている場合左クリックするとスターとする
		if (Novice::IsTriggerMouse(0) ) {
			flagChange_ = true;
		}
	}
	else {
		toTitleColor_.color = WHITE;
	}
#pragma endregion

}

