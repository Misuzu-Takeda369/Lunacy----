#include "TutrialSystem.h"

TutrialSystem::~TutrialSystem()
{
	delete tutrialtext_;
}

void TutrialSystem::Initialize(float Pspeedx)
{
	tutrialtext_ = new TutrialText();
	tutrialtext_->Initialize();

	moveDestance_ = 0.0f;
	playerSpeed_ = Pspeedx;
	pushBotton_ = 0;

	jumpCount_ = 0;

	countchange_ = 0;
	nowPMaind_ = Normal;
	nowPattack_ = Plane;

	IsDead_ = false;
	imageNum_ = 0;

	frameCool_ = 0;
}

void TutrialSystem::Update(MaindState Pmaind, PlayerAttackType Patteck)
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);


	switch (nowExprestion_)
	{
	case TutrialSystem::Move:
		///横移動

		imageNum_ = 0;
		//一定距離右方向へ進ませる
		if (keys[DIK_D] || keys[DIK_RIGHT]) {
			//推し続けているだけカウントが進む
			pushBotton_++;
		}

		moveDestance_ = float(pushBotton_) * playerSpeed_;

		if (moveDestance_ >= 400.0f) {
			//一定距離進んだらモードが変わる
			nowExprestion_ = Junp;
		}

		break;
	case TutrialSystem::Junp:

		///ジャンプ
		//画像表示
		if (jumpCount_ == 0) {
			imageNum_ = 1;
		}
		else if (jumpCount_ == 1) {
			imageNum_ = 2;
		}
		else if (jumpCount_ == 2) {
			imageNum_ = 3;
		}

		//3回飛ばせる
		if ((preKeys[DIK_W] == 0 && keys[DIK_W] != 0) || (preKeys[DIK_UP] == 0 && keys[DIK_UP] != 0)) {
			//押した分だけカウント
			jumpCount_++;
		}

		if (jumpCount_ >= 3) {
			nowExprestion_ = AttackNomal;
		}

		break;

	case TutrialSystem::AttackNomal:
		///攻撃(ゲームプレイの方で処理)
		imageNum_ = 4;
		//敵の当たり判定で追記したので特になし

		break;

	case TutrialSystem::NExplanation:
		///説明
		imageNum_ = 5;
		notAttackFrag_ = true;

		frameCool_++;
		//ゲージあげてチラ見せでもいいかもしれない
		if ((Novice::IsTriggerMouse(0)) && frameCool_ >= frameCoolMAX_) {
			nowExprestion_ = AttackLuna;
			frameCool_ = 0;
		}

		break;
	case TutrialSystem::AttackLuna:
		///攻撃(ゲームプレイの方で処理)
		notAttackFrag_ = false;
		imageNum_ = 6;

		break;

	case TutrialSystem::LExplanation:
		///最後の説明

		notAttackFrag_ = true;

		if (imageNum_ == 6) {
			imageNum_ = 7;
		}
		else if (imageNum_ == 7) {
			frameCool_++;

			if (Novice::IsTriggerMouse(0) && frameCool_ >= frameCoolMAX_) {
				imageNum_ = 8;
				frameCool_ = 0;
			}

		}
		else if (imageNum_ == 8) {
			frameCool_++;

			if (Novice::IsTriggerMouse(0) && frameCool_ >= frameCoolMAX_) {
				imageNum_ = 9;
				frameCool_ = 0;
			}
		}
		else if (imageNum_ == 9) {
			frameCool_++;

			if (Novice::IsTriggerMouse(0) && frameCool_ >= frameCoolMAX_) {
				frameCool_ = 0;
				//狂気ゲージの為
				nowExprestion_ = none;
				notAttackFrag_ = false;
				IsDead_ = true;
			}
		}

		break;
	default:
		break;
	}

	///旧チュートリアル
	//switch (nowExprestion_)
	//{
	//case TutrialSystem::Move:
	//	//画像num
	//	imageNum_ = 0;
	//	//一定距離右方向へ進ませる
	//	if (keys[DIK_D] || keys[DIK_RIGHT]) {
	//		//推し続けているだけカウントが進む
	//		pushBotton_++;
	//	}

	//	moveDestance_ = float(pushBotton_) * playerSpeed_;

	//	if (moveDestance_ >= 400.0f) {
	//		//一定距離進んだらモードが変わる
	//		nowExprestion_ = Junp;
	//	}
	//	break;

	//case TutrialSystem::AttackNomal:
	//	imageNum_ = 4;
	//	//敵の当たり判定で追記したので特になし
	//	break;
	//case TutrialSystem::AttackChange:

	//	//画像表示の為の処理
	//	if (countchange_ == 0) {
	//		imageNum_ = 5;
	//	}
	//	else if (countchange_ == 1) {
	//		imageNum_ = 6;
	//	}
	//	else if (countchange_ == 2) {
	//		imageNum_ = 7;
	//	}

	//	//右クリック3回押す
	//	if (Novice::IsTriggerMouse(1)) {
	//		nowPattack_ = Patteck;
	//		countchange_++;
	//	}

	//	if (countchange_ >= 3) {
	//		nowExprestion_ = AttackMagic;
	//	}

	//	break;
	//case TutrialSystem::AttackMagic:
	//	//倒す(2回目)
	//	imageNum_ = 8;
	//	break;
	//case TutrialSystem::LunaMode:

	//	if (imageNum_ == 8) {
	//		imageNum_ = 9;
	//	}
	//	frameCool_++;
	//	//ゲージあげてチラ見せでもいいかもしれない
	//	if (Novice::IsTriggerMouse(0)) {
	//		if (imageNum_ == 9 && frameCool_>= frameCoolMAX_) {
	//			imageNum_ = 10;
	//			frameCool_ = 0;
	//		}
	//		else if (imageNum_ == 10 && frameCool_ >= frameCoolMAX_) {
	//			nowExprestion_ = Free;
	//			frameCool_ = 0;
	//		}
	//		
	//	}
	//	break;
	//case TutrialSystem::Free:

	//	imageNum_ = 11;
	//	frameCool_++;
	//	if (Novice::IsTriggerMouse(0) && frameCool_ >= frameCoolMAX_) {
	//		IsDead_ = true;
	//	}

	//	break;
	//case TutrialSystem::Junp:
	//	
	//	//画像表示の為の処理
	//	if (jumpCount_== 0) {
	//		imageNum_ = 1;
	//	}
	//	else if (jumpCount_ == 1) {
	//		imageNum_ = 2;
	//	}
	//	else if (jumpCount_ == 2) {
	//		imageNum_ = 3;
	//	}

	//	//3回飛ばせる
	//	if ((preKeys[DIK_W] == 0 && keys[DIK_W] != 0 )|| (preKeys[DIK_UP] == 0 && keys[DIK_UP] != 0)) {
	//		//押した分だけカウント
	//		jumpCount_++;
	//	}

	//	if (jumpCount_ >= 3) {
	//		nowExprestion_ = AttackNomal;
	//	}

	//	break;

	//default:
	//	break;
	//}


	tutrialtext_->SetImageNum(imageNum_);
	tutrialtext_->Update();
}

void TutrialSystem::Draw()
{
	tutrialtext_->Draw();

#ifdef _DEBUG
	//変移確認用(後で消滅させる邪魔だし)
	//switch (nowExprestion_)
	//{
	//case TutrialSystem::Move:

	//	Novice::ScreenPrintf(900, 300, "0");
	//	break;
	//case TutrialSystem::AttackNomal:

	//	Novice::ScreenPrintf(900, 300, "1");
	//	break;
	//case TutrialSystem::AttackChange:

	//	Novice::ScreenPrintf(900, 300, "2");
	//	break;
	//case TutrialSystem::AttackMagic:

	//	Novice::ScreenPrintf(900, 300, "3");
	//	break;
	//case TutrialSystem::LunaMode:

	//	Novice::ScreenPrintf(900, 300, "4");
	//	break;
	//case TutrialSystem::Free:

	//	Novice::ScreenPrintf(900, 300, "5");
	//	break;
	//case TutrialSystem::Junp:
	//	Novice::ScreenPrintf(900, 300, "6");
	//	break;


	//default:
	//	break;
	//}

	switch (nowExprestion_)
	{
	case TutrialSystem::Move:

		Novice::ScreenPrintf(900, 300, "0");
		break;
	case TutrialSystem::Junp:

		Novice::ScreenPrintf(900, 300, "1");
		break;

	case TutrialSystem::AttackNomal:

		Novice::ScreenPrintf(900, 300, "2");
		break;

	case TutrialSystem::NExplanation:

		Novice::ScreenPrintf(900, 300, "3");
		break;
	case TutrialSystem::AttackLuna:

		Novice::ScreenPrintf(900, 300, "4");
		break;

	case TutrialSystem::LExplanation:
	
		Novice::ScreenPrintf(900, 300, "5");
		break;
	default:
		break;
	}


	Novice::ScreenPrintf(900, 350, "flag:%d",notAttackFrag_);
#endif // _DEBUG


}
