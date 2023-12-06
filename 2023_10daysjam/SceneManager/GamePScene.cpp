#include "GamePScene.h"


GamePScene::~GamePScene()
{
	delete player_;
	delete hpUi_;
	delete spUi_;
	delete timerUi_;
	delete backGround_;
	delete waveTextUi_;

	delete tutrialSystem_;

	//delete enemy_;

	for (PopEnemy* enemies : enemy_) {
		delete enemies;
	}



	for (PopItem* popItem : popItem_) {
		delete popItem;
	}


}

void GamePScene::Initialize(Wave& nowWave)
{
	CountNum_ = 0;
	player_ = new Player();
	player_->Initialize();


	hpUi_ = new HpUI();
	hpUi_->Initialize();

	spUi_ = new SpUI();
	spUi_->Initialize();

	timerUi_ = new TimerUI();
	timerUi_->Initialize();

	backGround_ = new BackGround();
	backGround_->Initialize();

	//多分後で変わる(初期化内容からがっつり変わる可能性)
	nowWave_ = nowWave;

	waveTextUi_ = new WaveTextUI;
	waveTextUi_->Initialize(nowWave_);



	tutrialSystem_ = new TutrialSystem;
	tutrialSystem_->Initialize(player_->GetPlayerSpeedX());

	//ここで敵を産むすぐに殺す
	/*enemyImage_[0];
	enemyImage_[1];
	enemyImage_[2];
	enemyImage_[3];*/
	//ここで敵を産むすぐに殺す(重くなるタイミングが2回出てきた)
}

void GamePScene::Initialize()
{
	CountNum_ = 0;
	player_ = new Player();
	player_->Initialize();


	hpUi_ = new HpUI();
	hpUi_->Initialize();

	spUi_ = new SpUI();
	spUi_->Initialize();

	timerUi_ = new TimerUI();
	timerUi_->Initialize();

	backGround_ = new BackGround();
	backGround_->Initialize();


	//多分後で変わる(初期化内容からがっつり変わる可能性)
	nowWave_ = Tutorial;

}

void GamePScene::Update()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	changeTimingFrame_++;

	//プレイモードがポーズか
	switch (gameSModeNow_)
	{
	case None:

		//止まってるか動いているか
		if (!GameMove_) {
			//ここ押すと動き出す
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
				GameMove_ = true;
			}

			if ((timerUi_->GetterTimer() <= 0) || ((player_->GetHp() <= 0) || (player_->GetSp() <= 0))) {
				flagChange_ = true;
			}


		}
		else {

#pragma region 特定のWaveでしか機能しない
			switch (nowWave_)
			{
			case Tutorial:

				tutrialSystem_->Update(player_->GetMaindStateNow(), player_->GetPlayerAttackTypeNow());

				if (tutrialSystem_->GetNowExprestion() == 4) {
					player_->SetSpChangingPoint(500.0f);
				}
				else {
					player_->SetSpChangingPoint(250.0f);
				}

				break;
			case Wave1:

				break;

			case Wave2:



				break;

			case Wave3:


				break;
			default:
				break;
			}
#pragma endregion

			//敵の発生
			//EnemyPoping();
			EnemyPoping(nowWave_);

			//ここプレイヤーからUIに変化点を受け取っておく
			spUi_->SetSpChangingPoint(player_->GetSpChangingPoint());

			//プレイヤーの挙動
			player_->Update(keys, preKeys);

			//敵の動き
			for (PopEnemy* enemies : enemy_) {
				enemies->Update();
			}

			//アイテムの挙動
			for (PopItem* popItem : popItem_) {
				if (!popItem->IsDead()) {
					popItem->Update();
				}
			}

			//当たり判定
			CheckCollisionAll();

			//敵を消去してよいか
			EnemyDead();
			//アイテムを消してよいか
			ItemDead();
#pragma region UI関連


			hpUi_->Update(player_->GetDecreasedHp());

			spUi_->Update(player_->GetDecreasedSp());

			timerUi_->Update(nowWave_);

#pragma endregion

			WaveChange();
			waveTextUi_->Update(nowWave_);

#pragma region シーン変更含む


			///ポーズへ
			if ((preKeys[DIK_P] == 0 && keys[DIK_P] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				GameMove_ = false;
				gameSModeNow_ = Pause;
				changeTimingFrame_ = 0;
			}
			//確認用
			CountNum_ += 1;
			///シーン変換
#ifdef _DEBUG
			//ここのif文でシーン移行出来るかを判別
			//現在はIを押したときに移動
			if ((preKeys[DIK_I] == 0 && keys[DIK_I] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {

				if (nowWave_ == Wave3) {
					flagChange_ = true;
					changeTimingFrame_ = 0;
					nowWave_ = Tutorial;
				}
			}
			//ここのif文でシーン移行出来るかを判別
			//現在はOを押したときに移動(がめおべ)
			if ((preKeys[DIK_O] == 0 && keys[DIK_O] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				flagGameOver_ = true;
				changeTimingFrame_ = 0;
			}
#endif // DEBUG

			if (timerUi_->GetterTimer() <= 0) {
				if (nowWave_ == Wave3) {
					flagChange_ = true;
					changeTimingFrame_ = 0;
					nowWave_ = Tutorial;
				}
			}
			//ここのif文でシーン移行出来るかを判別
			//現在はOを押したときに移動(がめおべ)
			if ((player_->GetHp() <= 0) || (player_->GetSp() <= 0)) {
				//flagChange_ = true;
				flagGameOver_ = true;
				GameMove_ = false;
			}

#pragma endregion 
		}

		break;

	case Pause:


		//解除
		if ((preKeys[DIK_P] == 0 && keys[DIK_P] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
			GameMove_ = true;
			gameSModeNow_ = None;
			changeTimingFrame_ = 0;
		}

		break;

	default:
		break;
	}


#ifdef _DEBUG
#pragma region ImGui関連

	ImGui::Begin("GameMove&Mode");
	ImGui::Text("GameMove_ %d\n0_Stop Butten[DIK_SPACE]\n", GameMove_);
	ImGui::Text("gameSModeNow_ %d\n0_None 1_Pause Butten[DIK_P]\n", gameSModeNow_);
	ImGui::End();

	ImGui::Begin("EnemyPop");
	ImGui::Text("EnemyPop %d\nWave1 260,wave2&3 180\n", EnemyPopFrame_);
	ImGui::End();

	ImGui::Begin("Wave");
	ImGui::Text("Wave %d\n[DIK_0]WaveChange", nowWave_);
	ImGui::End();


#pragma endregion
#endif // DEBUG
}

void GamePScene::Draw()
{

	backGround_->Draw();

#pragma region 特定のWAVEのみに写る処理
	switch (nowWave_)
	{
	case Tutorial:

		tutrialSystem_->Draw();

		break;

	case Wave1:

		break;

	case Wave2:

		break;

	case Wave3:

		break;

	default:
		break;
	}
#pragma endregion

	player_->Draw();

	for (PopEnemy* enemies : enemy_) {

		//if (enemies->GetIsDead()) {
		enemies->Draw();
		//}

	}

	for (PopItem* popItem : popItem_) {
		if (!popItem->IsDead()) {
			popItem->Draw();
		}
	}



#ifdef _DEBUG
	Novice::ScreenPrintf(500, 500, "%d", CountNum_);
	Novice::ScreenPrintf(500, 600, "%d", enemyNotAppeared_);

#endif // _DEBUG

#pragma region UI関連(一番前に写す)
	hpUi_->Draw();
	spUi_->Draw();
	timerUi_->Draw();
	waveTextUi_->Draw();

	/*switch (gameSModeNow_)
	{
	case None:

		break;

	default:
		break;
	}*/
#pragma endregion


}

void GamePScene::CheckCollisionAll()
{

	const std::list<PlayerLAttack*>& playerLA = player_->GetBullet();
	PlayerMAttack* playerMA = player_->GetMAttack();
	//アイテム(複数)


#pragma region プレイヤー本体と敵本体
	//player_->OnCollision();
	for (PopEnemy* enemies : enemy_) {

		if (IsCollision(player_, enemies) == true) {
			float damege = enemies->GetAttackPoint();
			EnemyType enemytype = enemies->GetEnemyType();
			player_->OnCollision(damege, enemytype);
			//enemies->
		}
		//enemies;


	}
#pragma endregion


#pragma region プレイヤー近距離と敵本体
	if (playerMA) {
		for (PopEnemy* enemies : enemy_) {

			if (IsCollision(playerMA, enemies) == true) {
				float damege = playerMA->GetAttackPoint();
				enemies->OnCollision(damege);

				///チュートリアル用
				if ((tutrialSystem_->GetNowExprestion() == 1) && (enemies->GetIsDead() == true)) {
					tutrialSystem_->SetNowExprestion(2);
				}
				///チュートリアル用
				if ((tutrialSystem_->GetNowExprestion() == 3) && (enemies->GetIsDead() == true)) {
					tutrialSystem_->SetNowExprestion(4);
				}
			}

		}
	}
#pragma endregion

#pragma region プレイヤー遠距離と敵本体


	for (PopEnemy* enemies : enemy_) {


		for (PlayerLAttack* playerLAtteck : playerLA) {

			if (playerLAtteck) {

				if (IsCollision(playerLAtteck, enemies) == true) {

					float damege = playerLAtteck->GetAttackPoint();
					enemies->OnCollision(damege);
					playerLAtteck->OnCollision();


					///チュートリアル用(事故った時用)
					if ((tutrialSystem_->GetNowExprestion() == 1) && (enemies->GetIsDead() == true)) {
						tutrialSystem_->SetNowExprestion(2);
					}
					///チュートリアル用
					if ((tutrialSystem_->GetNowExprestion() == 3) && (enemies->GetIsDead() == true)) {
						tutrialSystem_->SetNowExprestion(4);
					}

				}
			}

		}

	}
#pragma endregion

#pragma region プレイヤー本体とアイテム
	for (PopItem* popItem : popItem_) {
		//ここで動いたのでプレイヤー関連では無さソう
		//float recover = popItem->GetRecoverState();
		//player_->UsedItem(recover);


		if (IsCollision(player_, popItem) == true) {
			float recover = popItem->GetRecoverState();
			player_->UsedItem(recover);
			popItem->OnColistion();
		}


		//enemies;


	}
#pragma endregion
}

void GamePScene::ItemDead()
{

	popItem_.remove_if([](PopItem* popItem) {
		if (popItem->IsDead()) {
			delete popItem;
			return true;
		}

		return false;
		});


	/*
	if (popItem_->IsDead()) {
		delete popItem_;
	}
	*/
}

void GamePScene::EnemyDead()
{
	for (PopEnemy* enemies : enemy_) {
		if (enemies->GetIsDead()) {
			int rum = RandomRange(1, 2);

			if (rum % 2 == 0) {

				PopItem* newItem = new PopItem();
				Vector2 pos = { enemies->GetPosX(), enemies->GetPosY() };
				newItem->Initialize(pos);

				popItem_.push_back(newItem);
			}
		}
	}

	enemy_.remove_if([](PopEnemy* enemies) {
		if (enemies->GetIsDead()) {
			delete enemies;
			return true;
		}

		return false;
		});

}

//void GamePScene::EnemyPoping()
//{
//	EnemyPopFrame_++;
//
//	if (EnemyPopFrame_ >= consEnemyPopFrameWave1_) {
//
//
//		PopEnemy* newEnemy = new PopEnemy();
//
//		newEnemy->Initialize(player_->GetMaindStateNow(), nowWave_);
//		enemy_.push_back(newEnemy);
//		EnemyPopFrame_ = 0;
//
//	}
//}

void GamePScene::EnemyPoping(Wave& nowWave)
{

	//Waveg事に枠タイミングを分けている
	switch (nowWave)
	{
	case Tutorial:

		if ((tutrialSystem_->GetNowExprestion() == 1) && countEnemy_ == 0) {
			PopEnemy* newEnemy = new PopEnemy();

			newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
			enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
			enemy_.push_back(newEnemy);
			countEnemy_ = 1;
		}

		if ((tutrialSystem_->GetNowExprestion() == 3) && countEnemy_ == 1) {
			PopEnemy* newEnemy = new PopEnemy();

			newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
			enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
			enemy_.push_back(newEnemy);
			countEnemy_ = 4;
		}

		break;

	case Wave1:

		EnemyPopFrame_++;

		if (EnemyPopFrame_ >= consEnemyPopFrameWave1_) {


			PopEnemy* newEnemy = new PopEnemy();
			newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
			enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
			enemy_.push_back(newEnemy);
			EnemyPopFrame_ = 0;

		}

		break;

	case Wave2:
		EnemyPopFrame_++;

		if (EnemyPopFrame_ >= consEnemyPopFrameWave2_) {


			PopEnemy* newEnemy = new PopEnemy();

			newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
			enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
			enemy_.push_back(newEnemy);
			EnemyPopFrame_ = 0;

		}

		break;
	case Wave3:
		EnemyPopFrame_++;

		if (EnemyPopFrame_ >= consEnemyPopFrameWave3_) {


			PopEnemy* newEnemy = new PopEnemy();

			newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
			enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
			enemy_.push_back(newEnemy);
			EnemyPopFrame_ = 0;

		}

		break;

	default:
		break;
	}

}

void GamePScene::WaveChange()
{
	if (tutrialSystem_->GetIsDead() == true) {
		delete tutrialSystem_;
	}
	//右クリック押したら終わる
	if ((nowWave_ == Tutorial) && tutrialSystem_->GetIsDead()) {
		nowWave_ = Wave1;
		GameMove_ = false;
		/*timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);*/
		player_->SetSp(player_->GetSpMax());
	}
	else if ((nowWave_ == Wave1) && (timerUi_->GetterTimer() <= 0)) {
		nowWave_ = Wave2;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);

	}
	else if ((nowWave_ == Wave2) && (timerUi_->GetterTimer() <= 0)) {
		nowWave_ = Wave3;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);
	}



#ifdef _DEBUG

	if ((nowWave_ == Tutorial) && (!keys[DIK_0] && preKeys[DIK_0])) {
		nowWave_ = Wave1;
		/*timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);*/
		waveTextUi_->Update(nowWave_);
	}
	else if ((nowWave_ == Wave1) && (!keys[DIK_0] && preKeys[DIK_0])) {
		nowWave_ = Wave2;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);
		waveTextUi_->Update(nowWave_);
	}
	else if ((nowWave_ == Wave2) && (!keys[DIK_0] && preKeys[DIK_0])) {
		nowWave_ = Wave3;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);
		waveTextUi_->Update(nowWave_);
	}



#endif // _DEBUG

}
