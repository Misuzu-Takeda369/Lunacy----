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
}

void TutrialSystem::Update(MaindState Pmaind, PlayerAttackType Patteck)
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	tutrialtext_->Update();

	switch (nowExprestion_)
	{
	case TutrialSystem::Move:
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
	case TutrialSystem::AttackNomal:
		//敵の当たり判定で追記したので特になし
		break;
	case TutrialSystem::AttackChange:
		//右クリック3回押す
		if (Novice::IsTriggerMouse(1)) {
			nowPattack_ = Patteck;
			countchange_++;
		}

		if (countchange_ >= 3) {
			nowExprestion_ = AttackMagic;
		}

		break;
	case TutrialSystem::AttackMagic:
		//倒す(2回目)
		break;
	case TutrialSystem::LunaMode:
		//ゲージあげてチラ見せでもいいかもしれない
		if (Novice::IsTriggerMouse(0)) {
			nowExprestion_ = Free;
		}
		break;
	case TutrialSystem::Free:

		//if (Novice::IsTriggerMouse(0)) {
			IsDead_ = true;
		//}

		break;
	case TutrialSystem::Junp:
		//3回飛ばせる
		if ((preKeys[DIK_W] == 0 && keys[DIK_W] != 0 )|| (preKeys[DIK_UP] == 0 && keys[DIK_UP] != 0)) {
			//押した分だけカウント
			jumpCount_++;
		}

		if (jumpCount_ >= 3) {
			nowExprestion_ = AttackNomal;
		}
	default:
		break;
	}
}

void TutrialSystem::Draw()
{
	tutrialtext_->Draw();

#ifdef _DEBUG
	//変移確認用(後で消滅させる邪魔だし)
	switch (nowExprestion_)
	{
	case TutrialSystem::Move:

		Novice::ScreenPrintf(900, 300, "0");
		break;
	case TutrialSystem::AttackNomal:

		Novice::ScreenPrintf(900, 300, "1");
		break;
	case TutrialSystem::AttackChange:

		Novice::ScreenPrintf(900, 300, "2");
		break;
	case TutrialSystem::AttackMagic:

		Novice::ScreenPrintf(900, 300, "3");
		break;
	case TutrialSystem::LunaMode:

		Novice::ScreenPrintf(900, 300, "4");
		break;
	case TutrialSystem::Free:

		Novice::ScreenPrintf(900, 300, "5");
		break;
	case TutrialSystem::Junp:
		Novice::ScreenPrintf(900, 300, "6");
		break;


	default:
		break;
	}
#endif // _DEBUG


}
