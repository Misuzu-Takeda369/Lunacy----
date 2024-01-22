#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize()
{
	titleImage_ = Novice::LoadTexture("./Resources/images/Text/Title.png");
	startImage_ = Novice::LoadTexture("./Resources/images/Text/Start.png");
	titleBack_= Novice::LoadTexture("./Resources/images/Back/Titleback_2.png");

	selectEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_system26.wav");
	decisionEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_system13.wav");

	OnselectNextPlay_ = false;
	OnselectBookPlay_ = false;
	selectEffectPlay_ = 0;
	//decisionEffecttPlay_ = 0;

	startPos_ = {
		750,350
	};
	startColor_ = { 255,255,255,255,0xFFFFFFFF };

	changeTimingFrame_ = 0;

	bookMark_ = Novice::LoadTexture("./Resources/images/databook.png");


	chackTextPos_[0] = { 330, 200 };
	chackTextPos_[1] = { 330, 200 };

	//チェック用
	chackColor_[0] = { 0,0,0,0,0xFFFFFFFF };
	chackColor_[1] = { 0,0,0,0,0xFFFFFFFF };
	//音が連続でならないようにするやつ
	OnSelectPChackPlay_[0] = false;
	OnSelectPChackPlay_[1] = false;

	textFrameImage_ = Novice::LoadTexture("./Resources/images/Back/Textfream.png");
	yesImage_ = Novice::LoadTexture("./Resources/images/Text/ChackYES.png");
	noImage_ = Novice::LoadTexture("./Resources/images/Text/ChackNO.png");
	chacktextImage_ = Novice::LoadTexture("./Resources/images/Text/ChackR.png");

}

void TitleScene::Update()
{

	switch (titleSModeNow_)
	{
	case None:
		//キーの処理
		memcpy(preKeys, preKeys, 256);
		Novice::GetHitKeyStateAll(keys);

		//ここのif文でシーン移行出来るかを判別
		
		changeTimingFrame_++;
		//マウスでのシーン移動
		MouseBottonChack();

#ifdef _DEBUG
		//現在は1を押したときに移動
		if ((preKeys[DIK_I] == 0 && keys[DIK_I] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
			flagChange_ = true;
			changeTimingFrame_ = 0;
		}

#endif // _DEBUG
		break;

	case Expriense:

		break;
		/*今は多分いらん
			case Option:
				break;*/

	case Chackreset:

		ResetPlayChack();

		break;
	default:
		break;
	}
}

void TitleScene::Draw()
{
	//背景‽の色
	//Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x30182CFF, kFillModeSolid);
	Novice::DrawSprite(0, 0, titleBack_, 1.0f/2.0f, 1.0f / 2.0f, 0.0f, WHITE);
	//タイトル
	Novice::DrawSprite(startPos_.x_ - 200,50, titleImage_,1.0f,1.0f,0.0f,WHITE);
	//文字の奴
	Novice::DrawSprite(startPos_.x_, startPos_.y_, startImage_, 1.0f, 1.0f, 0.0f, startColor_.color);

	Novice::DrawSprite(bookPos_.x_, bookPos_.y_, bookMark_, 0.25f, 0.25f, 0, bookColor_.color);

	//タイトルから移動する前に確認させる用の描写
	if (titleSModeNow_== Chackreset) {

		Novice::DrawSprite(330, 200, textFrameImage_, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(330, 200, chacktextImage_, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(chackTextPos_[0].x_, chackTextPos_[0].y_, yesImage_, 1, 1, 0.0f, chackColor_[0].color);
		Novice::DrawSprite(chackTextPos_[1].x_, chackTextPos_[1].y_, noImage_, 1, 1, 0.0f, chackColor_[1].color);

	}
	
}

void TitleScene::MouseBottonChack()
{
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);


	if ((mousePos_.x_>= startPos_.x_ && mousePos_.x_ <= startPos_.x_+ startSizeX_)
		&&
		(mousePos_.y_ >= startPos_.y_ && mousePos_.y_ <= startPos_.y_ + startSizeY_))
	{
		startColor_.color = RED;

		//連続でならないようにするやつ
		if (OnselectNextPlay_ == false) {

			OnselectNextPlay_ = true;

			//マウスに触れたときに音が鳴る
			if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
				Novice::PlayAudio(selectEffect_, 0, 1);
			}
		}

		//はじめるに入っている場合左クリックするとスターとする
		if (Novice::IsTriggerMouse(0) && changeTimingFrame_ >= changeTimingFrameMax_) {
			
			//リセットするか？
			if (maxWave_ !=0) {
				titleSModeNow_ = Chackreset;
			}
			else {
				flagChange_ = true;
			}
		
			changeTimingFrame_ = 0;

			Novice::StopAudio(selectEffect_);
			Novice::PlayAudio(decisionEffect_, 0, 2);
		}
	}
	else {
		startColor_.color = WHITE;
		OnselectNextPlay_ = false;
	}

	//セーブデータの奴
	if ((mousePos_.x_ >= bookPos_.x_ && mousePos_.x_ <= bookPos_.x_ + bookSize_)
		&&
		(mousePos_.y_ >= bookPos_.y_ && mousePos_.y_ <= bookPos_.y_ + bookSize_)) {

		bookColor_.color = RED;

		//連続でならないようにするやつ
		if (OnselectBookPlay_ == false) {

			OnselectBookPlay_ = true;

			//マウスに触れたときに音が鳴る
			if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
				Novice::PlayAudio(selectEffect_, 0, 1);
			}
		}

		if (Novice::IsTriggerMouse(0)) {
			toPlayData_ = true;
			Novice::StopAudio(selectEffect_);
			Novice::PlayAudio(decisionEffect_, 0, 2);
		}
	}
	else {
		bookColor_.color = WHITE;
		OnselectBookPlay_ = false;
	}

}

void TitleScene::ResetPlayChack()
{
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);

	//YES
	if ((mousePos_.x_ >= chackTextPos_[0].x_ && mousePos_.x_ <= chackTextPos_[0].x_ + size_.x_)
		&&
		(mousePos_.y_ >= chackTextPos_[0].y_ + 100 && mousePos_.y_ <= chackTextPos_[0].y_ + 100 + size_.y_))
	{

		chackColor_[0].color = RED;

		//連続でならないようにするやつ
		if (OnSelectPChackPlay_[0] == false) {

			OnSelectPChackPlay_[0] = true;

			//マウスに触れたときに音が鳴る
			if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
				Novice::PlayAudio(selectEffect_, 0, 1);
			}
		}

		if (Novice::IsTriggerMouse(0)) {

			flagChange_ = true;
			onReset_ = true;
			titleSModeNow_ = None;

			Novice::StopAudio(selectEffect_);
			Novice::PlayAudio(decisionEffect_, 0, 2);

		}

	}
	else {
		chackColor_[0].color = WHITE;
		OnSelectPChackPlay_[0] = false;
	}

	//NO
	if ((mousePos_.x_ >= chackTextPos_[1].x_ + 350 && mousePos_.x_ <= chackTextPos_[1].x_ + 350 + size_.x_)
		&&
		(mousePos_.y_ >= chackTextPos_[1].y_ + 100 && mousePos_.y_ <= chackTextPos_[1].y_ + 100 + size_.y_))
	{

		chackColor_[1].color = RED;

		//連続でならないようにするやつ
		if (OnSelectPChackPlay_[1] == false) {

			OnSelectPChackPlay_[1] = true;

			//マウスに触れたときに音が鳴る
			if (Novice::IsPlayingAudio(selectEffectPlay_) == 0) {
				Novice::PlayAudio(selectEffect_, 0, 1);
			}
		}

		if (Novice::IsTriggerMouse(0)) {
			flagChange_ = true;
			onReset_ = false;
			titleSModeNow_ = None;

			Novice::StopAudio(selectEffect_);
			Novice::PlayAudio(decisionEffect_, 0, 2);
		}

	}
	else {
		chackColor_[1].color = WHITE;
		OnSelectPChackPlay_[1] = false;
	}
}



