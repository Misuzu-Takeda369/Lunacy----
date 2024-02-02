#include "Player.h"
#include "ScreenSize.h"

Player::~Player()
{
	delete mAttack_;
	for (PlayerLAttack* lAttack : lAttack_) {
		delete lAttack;
	}

	delete playerAnimation_;

	delete jewel_;
}

void Player::Initialize()
{
	standardPos_ = { 150.0f,550.0f };

	charaBase_ = {
		{standardPos_.x,standardPos_.y},{5.0f,-1.8f },64.0f,0.0f,WHITE
	};

	hp_ = maxHp_;
	sp_ = maxSp_;

	decreasedHp_ = maxHp_ - hp_;
	decreasedSp_ = maxSp_ - sp_;

	jumpSpeed_ = baseJumpSpeed_;

	jumpFrag_ = false;
	//jumpLag_ = 10;

	playerAttackTypeNow_ = Plane;
	attackFrag_ = false;

	maindStateNow_ = Normal;
	maindColor_ = WHITE;
	spChangingPoint_ = 250.0f;

	playerDirectionA_ = RIGHT;
	playerDirectionM_ = RIGHT;

	attackframe_ = 10;

	playerState_ = IDOL;
	mousePos_ = { 0,0 };

	playerAnimation_ = new PlayerAnimation();
	playerAnimation_->Initialize();

	jewel_ = new PlayerJewel();
	jewel_->Initialize(charaBase_.color_);

	collisionType_ = Box;
	boxSize_ = { 32.0f,128.0f };


	hit_ = false;
	hitCoolTime_ = 0;

	getItem_ = false;
	getCoolTime_ = 0;

	///音響関連
	//音関連
	attackNomalEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/Sword_practice_swing1.wav");
	attackMacgiEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_magic_ice02.wav");
	walkEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/run_in_hall.wav");
	jumpEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/jump.wav");
	hitHpEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/Kick_practice2.wav");
	hitSpEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/maou_se_magical18.wav");
	usedItemEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/recovery_magic1.wav");
	changeAttackEffect_ = Novice::LoadAudio("./Resources/Music/SoundEffect/reflection.wav");

	//ハンドル
	attackNomalPlay_ = 0;
	attackMacgiPlay_ = 0;
	walkPlay_ = 0;
	jumpPlay_ = 0;
	hitHpPlay_ = 0;
	hitSpPlay_ = 0;
	usedItemPlay_ = 0;
	changeAttackPlay_ = 0;

	//画像
	magicImage_ = Novice::LoadTexture("./Resources/Images/Player_Magic.png");
}

void Player::Update(char* keys, char* preKeys)
{
	//移動処理
	Move(keys, preKeys);
	//攻撃モードの変移
	AttackTypeChange();

	//攻撃
	if (!notAttackFrag_) {
		Attack();
	}
	else {
		attackFrag_ = false;

		if (mAttack_) {
			delete mAttack_;
			mAttack_ = nullptr;
		}
	}

	//アニメーション
	playerAnimation_->Update(Vector2(charaBase_.pos_.x, charaBase_.pos_.y), playerState_, sabState_);
	playerAnimation_->SetDirection(playerDirectionM_);
	playerAnimation_->SetMaindState(maindStateNow_);
	playerAnimation_->SetJumpSpeed(jumpSpeed_);


	jewel_->Update(charaBase_.pos_, playerAttackTypeNow_, playerDirectionM_);
	//減った量
	//ゲージ処理用
	decreasedHp_ = maxHp_ - hp_;
	decreasedSp_ = maxSp_ - sp_;

	for (PlayerLAttack* lAttack : lAttack_) {

		lAttack->Update();
	}

	//弾の時間経過で消える処理
	BulletDead();
	//精神状態が変わるか否か
	MindTypeChange();

	//状態の奴
	PlayerStateChange(keys);

	//被弾クール
	CoolCheak();

	//アイテムゲットクール
	ItemCoolCheak();


#pragma region ImGum関連

#ifdef _DEBUG
	ImGui::Begin("Player");

	ImGui::Text("PlayerPos: x_%.2f, y_%.2f\nMove_AWSD&Dicrection\n", charaBase_.pos_.x, charaBase_.pos_.y);
	ImGui::Text("PlayerSpeed: x_%.2f, y_%.2f\n", charaBase_.speed_.x, charaBase_.speed_.y);
	ImGui::Text("playerAttackTypeNow: %d\n0_Nomal,1_Magic MouseRightBottun\n", playerAttackTypeNow_);
	ImGui::Text("maindStateNow: %d\n0_Nomal,1_Mad\n", maindStateNow_);
	ImGui::Text("attackFrag: %d\nMouseLeftBottun\n", attackFrag_);
	ImGui::Text("playerState: %d\n", playerState_);
	ImGui::InputFloat("Hp:", &hp_);
	ImGui::InputFloat("Sp:\n", &sp_);
	ImGui::InputFloat("spChangingPoint:", &spChangingPoint_);
	ImGui::InputFloat("attackSpDown:\n", &attackSpDown_);
	ImGui::Text("notAttackFrag_: %d\n", notAttackFrag_);

	ImGui::End();
#endif // DEBUG

#pragma endregion
}

void Player::Draw()
{

#ifdef _DEBUG
	//プレイヤー本体
	Novice::DrawEllipse(int(charaBase_.pos_.x), int(charaBase_.pos_.y), int(charaBase_.radius_), int(charaBase_.radius_), 0.0f, charaBase_.color_, kFillModeSolid);

	Novice::DrawLine(0, int(standardPos_.y + charaBase_.radius_), 1280, int(standardPos_.y + charaBase_.radius_), BLACK);
	Novice::DrawBox(900, 100, 50, 50, 0.0f, maindColor_, kFillModeSolid);
#endif // _DEBUG

	jewel_->Draw();
	playerAnimation_->Draw();

	//近距離用当たり判定が起きている時場合
	if (mAttack_) {
		mAttack_->Draw();
	}

	for (PlayerLAttack* lAttack : lAttack_) {
		lAttack->Draw();
	}

}

void Player::Draw(Vector2 ShakePos)
{

#ifdef _DEBUG
	//プレイヤー本体
	Novice::DrawEllipse(int(charaBase_.pos_.x), int(charaBase_.pos_.y), int(charaBase_.radius_), int(charaBase_.radius_), 0.0f, charaBase_.color_, kFillModeSolid);

	Novice::DrawLine(0, int(standardPos_.y + charaBase_.radius_), 1280, int(standardPos_.y + charaBase_.radius_), BLACK);
	Novice::DrawBox(900, 100, 50, 50, 0.0f, maindColor_, kFillModeSolid);
#endif // _DEBUG

	jewel_->Draw();
	playerAnimation_->Draw();

	//近距離用当たり判定が起きている時場合
	if (mAttack_) {
		mAttack_->Draw();
	}

	for (PlayerLAttack* lAttack : lAttack_) {
		lAttack->Draw();
	}

}

void Player::Move(char* keys, char* preKeys)
{

	if (1) {

		//横移動
		if (keys[DIK_LEFT] || keys[DIK_A]) {
			if (charaBase_.pos_.x >= MimWindowWidth + boxSize_.x) {
				charaBase_.pos_.x -= charaBase_.speed_.x;
			}
			playerDirectionM_ = LEFT;

			//ジャンプの時は消す(走行音)
			if (jumpFrag_) {
				Novice::StopAudio(walkPlay_);
			}
			else {
				if (Novice::IsPlayingAudio(walkPlay_) == 0) {
					walkPlay_ = Novice::PlayAudio(walkEffect_, 0, 0.4f);
				}
			}

			//playerState_ = MOVE;
		}
		else if (keys[DIK_RIGHT] || keys[DIK_D]) {
			if (charaBase_.pos_.x <= kWindowWidth - boxSize_.x) {
				charaBase_.pos_.x += charaBase_.speed_.x;
			}
			playerDirectionM_ = RIGHT;

			//ジャンプの時は消す(走行音)
			if (jumpFrag_) {
				Novice::StopAudio(walkPlay_);
			}
			else {
				if (Novice::IsPlayingAudio(walkPlay_) == 0) {
					walkPlay_ = Novice::PlayAudio(walkEffect_, 0, 0.4f);
				}
			}

			//playerState_ = MOVE;
		}
		else {
			Novice::StopAudio(walkPlay_);
		}

	}

	//縦
	Jump();

	if (((preKeys[DIK_UP] == 0 && keys[DIK_UP] != 0) || (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] !=0))) {

		if (Novice::IsPlayingAudio(jumpPlay_) == 0) {
			Novice::PlayAudio(jumpEffect_, 0, 1.5f);
		}

		jumpFrag_ = true;
	}

}

void Player::Jump()
{
	//ジャンプの挙動
	if (jumpFrag_) {

		if (jumpSpeed_ < 0) {
			jumpSpeed_ += -1.2f;
		}
		else {
			jumpSpeed_ += charaBase_.speed_.y;
		}
		charaBase_.pos_.y -= jumpSpeed_;


		if (charaBase_.pos_.y >= standardPos_.y) {
			jumpFrag_ = false;
			charaBase_.pos_.y = standardPos_.y;
			jumpSpeed_ = baseJumpSpeed_;
		}
	}
}

void Player::AttackTypeChange()
{
	//右クリックしたら攻撃のモードが変わる(攻撃中は変わらない)
	if (Novice::IsTriggerMouse(1) && !attackFrag_) {

		if (Novice::IsPlayingAudio(changeAttackPlay_) == 0) {
			Novice::PlayAudio(changeAttackEffect_, 0, 0.8f);
		}

		if (playerAttackTypeNow_ == Plane) {
			playerAttackTypeNow_ = Magic;
			charaBase_.color_ = RED;
		}
		else {
			playerAttackTypeNow_ = Plane;
			charaBase_.color_ = WHITE;
		}


	}

}


void Player::MindTypeChange()
{
	if (sp_ <= spChangingPoint_) {
		maindStateNow_ = Lunatic;
		maindColor_ = RED;
	}
	else {
		maindStateNow_ = Normal;
		maindColor_ = WHITE;
	}
}


void Player::Attack()
{
	//左クリックしたら攻撃する
	if (Novice::IsTriggerMouse(0) && !attackFrag_) {

		//プレイヤーの向き
		playerDirectionDecisionA();

		//現在SP使う攻撃の時に弾が出るようになる
		if ((playerAttackTypeNow_ == Magic)) {

			//効果音(魔法っぽいやつ)
			if (Novice::IsPlayingAudio(attackMacgiPlay_) == 0) {
				Novice::PlayAudio(attackMacgiEffect_, 0, 1);
			}

			PlayerLAttack* newlAttack = new PlayerLAttack();
			//newlAttack->Initialize(playerAttackTypeNow_, maindStateNow_, playerDirectionA_, charaBase_.pos_);
			newlAttack->Initialize(playerAttackTypeNow_, maindStateNow_, playerDirectionM_, charaBase_.pos_);
			lAttack_.push_back(newlAttack);

			for (PlayerLAttack* lAttack : lAttack_) {
				lAttack->SetImage(magicImage_);
			}
		}
		else {

			//効果音(ぶん回す音)
			//効果音(魔法っぽいやつ)
			if (Novice::IsPlayingAudio(attackNomalPlay_) == 0) {
				Novice::PlayAudio(attackNomalEffect_, 0, 0.8f);
			}
		}

		attackFrag_ = true;
		//SP関連の処理
		AttackSpDown();

		if (mAttack_) {
			delete mAttack_;
			mAttack_ = nullptr;
		}

		mAttack_ = new PlayerMAttack();
		//mAttack_->Initialize(playerAttackTypeNow_, maindStateNow_, playerDirectionA_);
		mAttack_->Initialize(playerAttackTypeNow_, maindStateNow_, playerDirectionM_);


		//攻撃力の設定
		mAttack_->DeterminingAttackPower(hp_, maxHp_, sp_, maxSp_);

		for (PlayerLAttack* lAttack : lAttack_) {
			lAttack->DeterminingAttackPower(hp_, maxHp_, sp_, maxSp_);
		}

	}

	//アタックフラグが動いている場合
	if (attackFrag_) {

		//近距離用当たり判定が起きている時場合
		if (mAttack_) {
			//mAttack_->Update(charaBase_.pos_, playerDirectionA_);
			mAttack_->Update(charaBase_.pos_, playerDirectionM_);

		}

		//アニメーション入るまで仮フレーム
		attackframe_--;
		if (attackframe_ <= 0) {
			attackFrag_ = false;
			delete mAttack_;

			mAttack_ = nullptr;

			attackframe_ = baseAttackFrame_;
		}
	}

}

void Player::BulletDead()
{
	lAttack_.remove_if([](PlayerLAttack* lAttack) {
		if (lAttack->IsDead()) {
			delete lAttack;
			return true;
		}

		return false;
		});
}

void Player::AttackSpDown()
{
	if (playerAttackTypeNow_ == Magic) {
		sp_ -= attackSpDown_;
	}
}

void Player::playerDirectionDecisionA()
{
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);

	int mouseToP = mousePos_.x_ - int(charaBase_.pos_.x);

	if (mouseToP >= 0) {
		playerDirectionA_ = RIGHT;
	}
	else {
		playerDirectionA_ = LEFT;
	}
}

void Player::PlayerStateChange(char* keys)
{
	//移動処理のモーションよりもジャンプの方が優先度高い
	if (attackFrag_) {
		if (playerAttackTypeNow_ == Plane) {
			//playerState_ = ATTACK;
			sabState_ = _ATTACK;
		}
		else if (playerAttackTypeNow_ == Magic) {
			//playerState_ = SKILL;
			sabState_ = _MAGIC;
		}
	}
	else {
		sabState_ = _NONE;
	}

	if (jumpFrag_) {
		playerState_ = JUMP;
	}
	else if ((keys[DIK_LEFT] || keys[DIK_A]) || (keys[DIK_RIGHT] || keys[DIK_D])) {
		playerState_ = MOVE;
	}
	else {
		playerState_ = IDOL;
	}

}

void Player::OnCollision(float& damage, EnemyType& enemytype)
{
	if (!hit_) {

		if (maindStateNow_ == Normal) {
			if (enemytype == HPNOMAL) {
				hp_ -= damage;
				hit_ = true;

				if (Novice::IsPlayingAudio(hitHpPlay_) == 0) {
					hitHpPlay_ = Novice::PlayAudio(hitHpEffect_, 0, 1);
				}
			}
			else {
				sp_ -= damage;
				hit_ = true;

				if (Novice::IsPlayingAudio(hitSpPlay_) == 0) {
					hitSpPlay_ = Novice::PlayAudio(hitSpEffect_, 0, 1);
				}
			}
		}
		else
		{
			///狂気モードの時に被弾したら通常時よりも減少量が増える
			if (enemytype == HPNOMAL) {
				hp_ -= damage + ((hitMagnification_ * decreasedHp_) + 10);
				hit_ = true;

				if (Novice::IsPlayingAudio(hitHpPlay_) == 0) {
					hitHpPlay_ = Novice::PlayAudio(hitHpEffect_, 0, 1);
				}
			}
			else {
				sp_ -= damage;
				hit_ = true;

				if (Novice::IsPlayingAudio(hitSpPlay_) == 0) {
					hitSpPlay_ = Novice::PlayAudio(hitSpEffect_, 0, 1);
				}
			}
		}




#ifdef _DEBUG
		charaBase_.color_ = BLACK;
#endif // _DEBUG

	}
}

void Player::OnContinuousDamage(float& damage, int& timer, bool& flag)
{

	if (flag) {

		hp_ -= damage;

		if (Novice::IsPlayingAudio(hitHpPlay_) == 0) {
			hitHpPlay_ = Novice::PlayAudio(hitHpEffect_, 0, 1);
		}
	}

	timer;
}

void Player::UsedItem(float& recover) {

	/*sp_ += recover;
	getItem_ = true;
	charaBase_.color_ = GREEN;*/


	if (!getItem_) {
		sp_ += recover;
		getItem_ = true;

		if (Novice::IsPlayingAudio(usedItemPlay_) == 0) {
			Novice::PlayAudio(usedItemEffect_, 0, 0.8f);
		}

		spChangingPoint_ += 2.0f;
		if (spChangingPoint_ >= maxSp_) {
			spChangingPoint_ = maxSp_;
		}


		if (sp_ >= maxSp_) {
			sp_ = maxSp_;
		}

#ifdef _DEBUG
		charaBase_.color_ = GREEN;
#endif // _DEBUG

	}

}

void Player::CoolCheak()
{
	if (hit_) {
		hitCoolTime_++;

		if (hitCoolTime_ >= MaxHitCoolTime_) {
			hit_ = false;
			hitCoolTime_ = 0;

#ifdef _DEBUG
			if (playerAttackTypeNow_ == Plane) {
				charaBase_.color_ = WHITE;
			}
			else {
				charaBase_.color_ = RED;
			}

#endif // _DEBUG
		}
	}

}

void Player::ItemCoolCheak()
{
	if (getItem_) {
		getCoolTime_++;

		if (getCoolTime_ >= MaxGetCoolTime_) {
			getItem_ = false;
			getCoolTime_ = 0;

#ifdef _DEBUG
			charaBase_.color_ = WHITE;
#endif // _DEBUG
		}
	}
}

void Player::StopMusic()
{
	Novice::StopAudio(attackNomalPlay_);
	Novice::StopAudio(attackMacgiPlay_);
	Novice::StopAudio(walkPlay_);
	Novice::StopAudio(jumpPlay_);
}

