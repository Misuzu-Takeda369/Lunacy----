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
	eHUi_->Initialize(charaBase_.pos_,6);

	///音響
	hitEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/blow6.wav");
	alarmEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/button02b.wav");
	//ハンドル
	hitPlay_ = 0;
	alarmPlay_ = 0;

	damageLimitTime_ = damageLimitTimeFMax_;

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

		ContinuousDamage();

		//ここがゲームシーンにこの個体が消滅している伝えるよう
		if (fhEnemy_->GetIsDead()) {
			isDead_ = true;
		}

		break;

	case SPNOMAL:

		break;

	default:
		break;
	}

	//ゲージ処理用(ゲージ未使用になったので不要に)
	//decreasedHp_ = maxHp_ - hp_;

	eHUi_->Update(hp_, charaBase_.pos_);


#ifdef _DEBUG
#pragma region ImGui関連

	ImGui::Begin("EnemyFryHp");
	ImGui::Text("EnemyFryHp %f\n", hp_);
	ImGui::Text("enemyNotAppeared_ %d\n", enemyNotAppeared_);
	ImGui::Text("damageLimitTime_ %d\n", damageLimitTime_);
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

	if (Novice::IsPlayingAudio(hitPlay_) == 0) {
		hitPlay_=Novice::PlayAudio(hitEffect_, 0, 0.5f);
	}



	if (!hit_) {
		hp_ -= damege;
		if (hp_ < 1.0f) {
			hp_ = 0.0f;
		}
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
		maxHp_ = fhEnemy_->GetHpMax();

		decreasedHp_ = maxHp_ - hp_;
		


		break;

	case SPNOMAL:


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

void FryingEnemy::ContinuousDamage()
{
	damageLimitTime_--;

	if (damageLimitTime_ / 60 == 1) {
		if (Novice::IsPlayingAudio(alarmPlay_) == 0) {
			alarmPlay_ = Novice::PlayAudio(alarmEffect_, 0, 0.8f);
		}
	}

	if (damageLimitTime_ <= 0) {
		damageFrag_ = true;
		damageLimitTime_ = damageLimitTimeMax_;
	}
	else {
		damageFrag_ = false;
	}
	
}




