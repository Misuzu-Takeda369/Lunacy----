#include "FryingPopEnemy.h"
#include "Novice.h"
#include "ImGuiManager.h"

FryingEnemy::~FryingEnemy()
{
	delete fhEnemy_;
}

void FryingEnemy::Initialize(MaindState maindStateNow, int enemyNotAppeared)
{

	charaBase_.pos_ = { 1400.f,200.0f };
	charaBase_.speed_ = { 0.8f,0.3f };
	charaBase_.radius_ = 50;

	maindStateNow_ = maindStateNow;

	countEnemy_ = 0;
	//rumNum_ = 1;
	//enemyType_ = NOMAL;

	collisionType_ = Circle;
	boxSize_ = { charaBase_.radius_,charaBase_.radius_ };

	enemyNotAppeared_ = enemyNotAppeared;

	/*if (enemyNotAppeared_ >= 2) {
		enemyNotAppeared_ = 0;
	}*/
	//敵の生成
	EnemyBorn();


	//Hpゲージ
	eHUi_ = new EHpUI();
	eHUi_->Initialize(charaBase_.pos_);

}

void FryingEnemy::Update()
{

	CoolCheak();

	switch (enemyType_)
	{
	case HPNOMAL:
		fhEnemy_->Update();

		attackPoint_ = fhEnemy_->GetAttackPoint();
		charaBase_.pos_.x = fhEnemy_->GetPosX();
		charaBase_.pos_.y = fhEnemy_->GetPosY();

		//ここがゲームシーンにこの個体が消滅している伝えるよう
		if (fhEnemy_->GetIsDead()) {
			isDead_ = true;
		}

		break;

	case SPNOMAL:

		//nSEnemy_->Update();

		//attackPoint_ = nSEnemy_->GetAttackPoint();
		//charaBase_.pos_.x = nSEnemy_->GetPosX();
		//charaBase_.pos_.y = nSEnemy_->GetPosY();

		////ここがゲームシーンにこの個体が消滅している伝えるよう
		//if (nSEnemy_->GetIsDead()) {
		//	isDead_ = true;
		//}
		break;

	default:
		break;
	}

	//ゲージ処理用
	decreasedHp_ = maxHp_ - hp_;

	eHUi_->Update(decreasedHp_, charaBase_.pos_);


#ifdef _DEBUG
#pragma region ImGui関連

	ImGui::Begin("EnemyHp");
	ImGui::Text("EnemyHp %f\n", hp_);
	ImGui::Text("enemyNotAppeared_ %d\n", enemyNotAppeared_);
	ImGui::End();

#pragma endregion
#endif // DEBUG
}

void FryingEnemy::Draw()
{

	switch (enemyType_)
	{
	case HPNOMAL:
		fhEnemy_->Draw();
		break;

	case SPNOMAL:
		//nSEnemy_->Draw();
		break;

	default:
		break;
	}


	eHUi_->Draw();
}

void FryingEnemy::OnCollision(float& damege)
{
	//damege;
	//hp_ -= 10.0f;

	if (!hit_) {
		hp_ -= damege;
		hit_ = true;
	}

	if (hp_ <= 0.0f) {
		isDead_ = true;
	}

}



void FryingEnemy::EnemyBorn()
{
	bool right = true;
	

#pragma region ポップした時の判別
	rumNum_ = RandomRange(1, 3);

	switch (rumNum_)
	{
	case 1:

		charaBase_.pos_.y = 200.0f;
		enemyType_ = HPNOMAL;
		enemyNotAppeared_ = 0;
		break;
	case 2:

		charaBase_.pos_.y = 400.0f;
		enemyType_ = HPNOMAL;
		enemyNotAppeared_ = 0;
		break;

	case 3:

		
		enemyType_ = NONE;
		enemyNotAppeared_++;

		break;

	default:
		break;
	}

#pragma endregion

	//出現
	switch (enemyType_)
	{
	case HPNOMAL:

		fhEnemy_ = new FHEnemy();
		fhEnemy_->Initialize(charaBase_.pos_, charaBase_.speed_, charaBase_.radius_);
		fhEnemy_->SetDirection(right);
		hp_ = fhEnemy_->GetHp();

		hp_ = fhEnemy_->GetHpMax();
		maxHp_ = (fhEnemy_->GetHpMax());

		decreasedHp_ = maxHp_ - hp_;
		


		break;

	case SPNOMAL:


		//nSEnemy_ = new NSEnemy();
		//nSEnemy_->Initialize(charaBase_.pos_, charaBase_.speed_, charaBase_.radius_);
		//nSEnemy_->SetDirection(right);

		//hp_ = nSEnemy_->GetHp();

		//maxHp_ = (nSEnemy_->GetHpMax());

		//decreasedHp_ = maxHp_ - hp_;

		break;

	default:
		isDead_ = true;
		break;
	}

}

void FryingEnemy::CoolCheak()
{
	if (hit_) {
		hitCoolTime_++;

		if (hitCoolTime_ >= MaxHitCoolTime_) {
			hit_ = false;
			hitCoolTime_ = 0;
		}
	}
}




