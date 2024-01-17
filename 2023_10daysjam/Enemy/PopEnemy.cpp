#include "PopEnemy.h"
#include "Novice.h"
#include "ImGuiManager.h"



PopEnemy::~PopEnemy()
{
	//delete E_Bullet;
	delete nHEnemy_;
	delete nSEnemy_;
	delete eHUi_;
}



void PopEnemy::Initialize(MaindState maindStateNow, Wave nowWave, int enemyNotAppeared)
{

	charaBase_.pos_ = { 1400.f,550.0f };
	charaBase_.speed_ = { 2.0f,0.3f };
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
	EnemyBorn(nowWave);


	//Hpゲージ
	eHUi_ = new EHpUI();
	eHUi_->Initialize(charaBase_.pos_, float(hp_));

	///音響
	hitEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/blow6.wav");
	walkEffect_ =Novice::LoadAudio("./Resources/Music/SoundEffect/Wriggling_tentacles.wav");
	//ハンドル
	hitPlay_ = 0;
	walkPlay_ = 0;

}

void PopEnemy::Update()
{

	CoolCheak();

	switch (enemyType_)
	{
	case HPNOMAL:
		nHEnemy_->Update();

		if (Novice::IsPlayingAudio(walkPlay_) == 0) {
			walkPlay_ = Novice::PlayAudio(walkEffect_, 0, 0.3f);
		}

		attackPoint_ = nHEnemy_->GetAttackPoint();
		charaBase_.pos_.x = nHEnemy_->GetPosX();
		charaBase_.pos_.y = nHEnemy_->GetPosY();

		//ここがゲームシーンにこの個体が消滅している伝えるよう
		if (nHEnemy_->GetIsDead()) {
			isDead_ = true;
		}

		break;

	case SPNOMAL:

		if (Novice::IsPlayingAudio(walkPlay_) == 0) {
			walkPlay_ = Novice::PlayAudio(walkEffect_, 0, 0.3f);
		}

		nSEnemy_->Update();

		attackPoint_ = nSEnemy_->GetAttackPoint();
		charaBase_.pos_.x = nSEnemy_->GetPosX();
		charaBase_.pos_.y = nSEnemy_->GetPosY();

		//ここがゲームシーンにこの個体が消滅している伝えるよう
		if (nSEnemy_->GetIsDead()) {
			isDead_ = true;
		}
		break;

	default:
		break;
	}


	eHUi_->Update(float(hp_), charaBase_.pos_);


#ifdef _DEBUG
#pragma region ImGui関連

	ImGui::Begin("EnemyHp");
	ImGui::Text("EnemyHp %f\n", hp_);
	ImGui::Text("enemyNotAppeared_ %d\n", enemyNotAppeared_);
	ImGui::End();

#pragma endregion
#endif // DEBUG
}

void PopEnemy::Draw()
{

	switch (enemyType_)
	{
	case HPNOMAL:
		nHEnemy_->Draw();
		break;

	case SPNOMAL:
		nSEnemy_->Draw();
		break;

	default:
		break;
	}


	eHUi_->Draw();
}

void PopEnemy::OnCollision(float& damege)
{
	//damege;
	//hp_ -= 10.0f;

	//効果音
	Novice::PauseAudio(walkPlay_);

	if (Novice::IsPlayingAudio(hitPlay_) == 0) {
		Novice::PlayAudio(hitEffect_, 0, 0.6f);
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

		Novice::StopAudio(walkPlay_);
	}

}

void PopEnemy::EnemyBorn(Wave nowWave)
{
	bool right = true;

	switch (nowWave)
	{
	case Tutorial:
		enemyType_ = HPNOMAL;
		right = true;

		break;
	case Wave1:

#pragma region ポップした時の判別
		rumNum_ = RandomRange(1, 3);
		//rumNum_ = 3;
		//
		if (rumNum_ == 1 || rumNum_ == 2) {
			enemyType_ = HPNOMAL;
			enemyNotAppeared_ = 0;
			right = true;
		}
		else if (rumNum_ == 3) {

			if (maindStateNow_ == Lunatic) {
				enemyType_ = SPNOMAL;
				enemyNotAppeared_ = 0;
				right = true;
			}
			else {
				if (enemyNotAppeared_ == 2) {
					enemyType_ = HPNOMAL;
					enemyNotAppeared_ = 0;
				}
				else {
					enemyType_ = NONE;
					enemyNotAppeared_++;
				}
			}

		}
		else {
			if (enemyNotAppeared_ >= 2) {
				enemyType_ = HPNOMAL;
				enemyNotAppeared_ = 0;
			}
			else {
				enemyType_ = NONE;
				enemyNotAppeared_++;
			}
		}




#pragma endregion
		break;
	case Wave2:
	case Wave3:
	case Wave4:

#pragma region ポップした時の判別
		rumNum_ = RandomRange(1, 5);

		//
		if (rumNum_ == 1) {
			enemyNotAppeared_ = 0;
			enemyType_ = HPNOMAL;

			right = true;
		}
		else if (rumNum_ == 2) {
			enemyNotAppeared_ = 0;
			enemyType_ = HPNOMAL;
			charaBase_.pos_.x = -100.0f;
			charaBase_.speed_.x = -charaBase_.speed_.x;
			right = false;
		}
		else if (rumNum_ == 3) {
			enemyNotAppeared_ = 0;
			if (maindStateNow_ == Lunatic) {
				enemyType_ = SPNOMAL;
			}
			else {
				enemyType_ = HPNOMAL;
			}
			right = true;
		}
		else if (rumNum_ == 4) {

			enemyNotAppeared_ = 0;
			if (maindStateNow_ == Lunatic) {
				enemyType_ = SPNOMAL;
			}
			else {
				enemyType_ = HPNOMAL;
			}

			charaBase_.pos_.x = -100.0f;
			charaBase_.speed_.x = -charaBase_.speed_.x;
			right = false;
		}
		else {
			if (enemyNotAppeared_ >= 2) {
				enemyType_ = HPNOMAL;
				enemyNotAppeared_ = 0;
			}
			else {
				enemyType_ = NONE;
				enemyNotAppeared_++;
			}
		}



#pragma endregion
		break;

	default:
		break;
	}


	//出現
	switch (enemyType_)
	{
	case HPNOMAL:

		nHEnemy_ = new NHEnemy();
		nHEnemy_->Initialize(charaBase_.pos_, charaBase_.speed_, charaBase_.radius_);
		nHEnemy_->SetDirection(right);
		//hp_ = nHEnemy_->GetHp();

		hp_ = nHEnemy_->GetHpMax();
		maxHp_ = (nHEnemy_->GetHpMax());

		decreasedHp_ = maxHp_ - hp_;


		break;

	case SPNOMAL:


		nSEnemy_ = new NSEnemy();
		nSEnemy_->Initialize(charaBase_.pos_, charaBase_.speed_, charaBase_.radius_);
		nSEnemy_->SetDirection(right);

		hp_ = nSEnemy_->GetHp();

		maxHp_ = (nSEnemy_->GetHpMax());

		decreasedHp_ = maxHp_ - hp_;

		break;

	default:
		isDead_ = true;
		break;
	}

}

void PopEnemy::CoolCheak()
{
	if (hit_) {
		hitCoolTime_++;

		if (hitCoolTime_ >= MaxHitCoolTime_) {
			hit_ = false;
			hitCoolTime_ = 0;
			Novice::ResumeAudio(walkPlay_);
		}
	}
}

void PopEnemy::StopMusic()
{
	Novice::StopAudio(walkPlay_);
	Novice::StopAudio(hitPlay_);
}



