#include "GamePScene.h"


GamePScene::~GamePScene()
{
	delete player_;
	delete hpUi_;
	delete spUi_;
	delete timerUi_;
	delete backGround_;
	delete waveTextUi_;
	delete apostelEvent_;

	delete tutrialSystem_;

	delete bossHpUi_;

	delete MindUi_;

	//delete enemy_;

	for (PopEnemy* enemies : enemy_) {
		delete enemies;
	}

	for (FryingEnemy* fryingenemis : fryingEnemy_) {
		delete fryingenemis;
	}


	for (PopItem* popItem : popItem_) {
		delete popItem;
	}

	delete hitEffect_;

	delete pouseMode_;

	delete bgm_;

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

	MindUi_ = new PlayerMindDisPlay();
	MindUi_->Initialize();

	tutrialSystem_ = new TutrialSystem;
	tutrialSystem_->Initialize(player_->GetPlayerSpeedX());

	apostelEvent_ = new ApostelEvent;
	apostelEvent_->Initialize();


	hitEffect_ = new HitEffect();
	hitEffect_->Initialize();

	bossHpUi_ = new BHpUI();
	bossHpUi_->Initialize();

	//敵のスポーン
	if (nowWave_ == Wave1) {
		EnemyPopFrame_ = consEnemyPopFrameWave1_;
	}
	else if (nowWave_ == Wave2) {
		EnemyPopFrame_ = consEnemyPopFrameWave2_;
	}
	else if (nowWave_ == Wave3) {
		EnemyPopFrame_ = consEnemyPopFrameWave3_;
	}

	pouseMode_ = new PouseMode();
	pouseMode_->Initialize();

	bgm_ = new BGMManage();
	bgm_->Initialize();

	fryEnemyPopFrame_ = consEnemyPopFrameFry_;

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

			startFrame_++;

			if (startFrame_ >= 10) {
				GameMove_ = true;
				startFrame_ = 0;
			}

#ifdef _DEBUG
			//ここ押すと動き出す
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
				GameMove_ = true;
			}
#endif // DEBUG


			//シーン変換(オーバーかクリアか)
			if (((player_->GetHp() <= 0) || (player_->GetSp() <= 0))) {
				//エフェクトぶち込んでもおもろそう
				flagChange_ = true;
			}

		}
		else {

#pragma region 特定のWaveでしか機能しない
			switch (nowWave_)
			{
			case Tutorial:

				tutrialSystem_->Update(player_->GetMaindStateNow(), player_->GetPlayerAttackTypeNow());

				///ゲージ
				if ((tutrialSystem_->GetNowExprestion() == 4) || (tutrialSystem_->GetNowExprestion() == 5)) {
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
				//飛ぶ敵の出現処理
				FryEnemyPoping();

				//敵の動き
				for (FryingEnemy* fryingenemis : fryingEnemy_) {
					fryingenemis->Update();
				}

				//敵の消滅条件
				FryingEnemyDead();

				break;

			case Boss:


				apostelEvent_->SetPlayerInfo(player_->GetCharaBase());
				apostelEvent_->Update();

				////Hp引っ張っていきたいのでごり押しでObjectへ変更
				//apostelObject = apostelEvent_->GetObjectInfo();
				//Hpゲージの挙動
				bossHpUi_->Update(apostelEvent_->GetDicHp());

				break;

			default:
				break;
			}
#pragma endregion

			//BGM用
			float Php = player_->GetHp();
			float Psp = player_->GetSp();
			Wave Nwa = nowWave_;

			//bgm_->Update(Php, Psp, Nwa);

			//敵の発生
			EnemyPoping(nowWave_);

			//ここプレイヤーからUIに変化点を受け取っておく
			spUi_->SetSpChangingPoint(player_->GetSpChangingPoint());

			//攻撃のリアクションするか
			ChackNotAttack();
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
			backGround_->SetPlayerSP(player_->GetSp(), player_->GetSpMax());
#pragma region UI関連


			hpUi_->Update(player_->GetDecreasedHp());

			spUi_->Update(player_->GetDecreasedSp());

			timerUi_->Update(nowWave_);

			//ここ...?
			hitEffect_->Update();

			MaindState Playernow = player_->GetMaindStateNow();
			MindUi_->Update(Playernow);
#pragma endregion

			WaveChange();
			waveTextUi_->Update(nowWave_);

#pragma region シーン変更含む


			if (((preKeys[DIK_P] == 0 && keys[DIK_P] != 0) || (pouseMode_->GetChangeFrag() == true)) && changeTimingFrame_ >= changeTimingFrameMax_) {

					GameMove_ = false;
					gameSModeNow_ = Pause;
					changeTimingFrame_ = 0;
					pouseMode_->SetChangeFrag(false);

					AllStopMusic();

			}

			////ポーズ関連の動き
			pouseMode_->Update(gameSModeNow_);
			
			gameSModeNow_ = pouseMode_->GetGameSModeNow();
			

			//確認用
			CountNum_ += 1;
			///シーン変換
#ifdef _DEBUG
			//ここのif文でシーン移行出来るかを判別
			//現在はIを押したときに移動
			if ((preKeys[DIK_I] == 0 && keys[DIK_I] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {

				if (nowWave_ == Boss) {
					flagChange_ = true;
					changeTimingFrame_ = 0;

					AllStopMusic();
				}

			}
			//ここのif文でシーン移行出来るかを判別
			//現在はOを押したときに移動(がめおべ)
			if ((preKeys[DIK_O] == 0 && keys[DIK_O] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
				flagChange_ = true;
				flagGameOver_ = true;
				changeTimingFrame_ = 0;

				AllStopMusic();
			}
#endif // DEBUG
			///クリア条件の変更
			if (apostelEvent_->GetIsDead()) {
				if (nowWave_ == Boss) {
					flagChange_ = true;
					changeTimingFrame_ = 0;

					//念のため
					AllStopMusic();
				}

			}
			//ここのif文でシーン移行出来るかを判別
			//現在はOを押したときに移動(がめおべ)
			if ((player_->GetHp() <= 0) || (player_->GetSp() <= 0)) {
				flagChange_ = true;
				flagGameOver_ = true;
				GameMove_ = false;

				AllStopMusic();
			}


#pragma endregion 
		}

		break;

	case Pause:

		//解除
		if (((preKeys[DIK_P] == 0 && keys[DIK_P] != 0) || (pouseMode_->GetChangeFrag() == true)) && changeTimingFrame_ >= changeTimingFrameMax_) {
			GameMove_ = true;
			gameSModeNow_ = None;
			changeTimingFrame_ = 0;
			pouseMode_->SetChangeFrag(false);
		}

		///ポーズからタイトルに戻る処理(ここじゃないとタイミングが変になる)
		if (pouseMode_->GettitleChangeFrag()) {

			flagChange_ = true;
			flagTitle_ = true;
			GameMove_ = false;
			gameSModeNow_ = None;
		}

		pouseMode_->Update(gameSModeNow_);
		gameSModeNow_ = pouseMode_->GetGameSModeNow();

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

	//backGround_->Draw();
	backGround_->Draw(hitEffect_->GetShakePos());

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

		//敵の動き
		for (FryingEnemy* fryingenemis : fryingEnemy_) {
			fryingenemis->Draw();
		}
		break;
	case Boss:

		apostelEvent_->Draw();
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
	//Novice::ScreenPrintf(500, 600, "%d", enemyNotAppeared_);


#endif // _DEBUG

	hitEffect_->Draw();

#pragma region UI関連(一番前に写す)

	/*hpUi_->Draw();
	spUi_->Draw();
	timerUi_->Draw();
	waveTextUi_->Draw();*/

	hpUi_->Draw(hitEffect_->GetShakePos());
	spUi_->Draw(hitEffect_->GetShakePos());

	if (nowWave_ == Boss) {
		bossHpUi_->Draw(hitEffect_->GetShakePos());
	}
	else {
		timerUi_->Draw(hitEffect_->GetShakePos());
	}
	waveTextUi_->Draw(hitEffect_->GetShakePos());

	MindUi_->Draw();


	///ここにポーズ関連の描写をまとめる

	switch (gameSModeNow_)
	{

	case None:

		pouseMode_->Draw(gameSModeNow_, hitEffect_->GetShakePos());
		break;

	case Pause:
		pouseMode_->Draw(gameSModeNow_, hitEffect_->GetShakePos());

		break;

	default:
		break;
	}
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
			hitEffect_->OnColistion(enemytype);
			enemies->AttackMotion();

		}
		//enemies;


	}
#pragma endregion


#pragma region プレイヤー近距離と敵本体
	if (playerMA) {
		for (PopEnemy* enemies : enemy_) {

				if ((IsCollision(playerMA, enemies) == true) && enemies->GetHit() == false) {

					ChackEToPDicrection(enemies);
					float damege = playerMA->GetAttackPoint();
					enemies->OnCollision(damege);

					///チュートリアル用
					if ((tutrialSystem_->GetNowExprestion() == 2) && (enemies->GetIsDead() == true)) {
						tutrialSystem_->SetNowExprestion(3);
					}
					///チュートリアル用
					if ((tutrialSystem_->GetNowExprestion() == 4) && (enemies->GetIsDead() == true)) {
						tutrialSystem_->SetNowExprestion(5);
					}

				}

		}
	}
#pragma endregion

#pragma region プレイヤー遠距離と敵本体


	for (PopEnemy* enemies : enemy_) {


		for (PlayerLAttack* playerLAtteck : playerLA) {

			if (playerLAtteck) {

				if ((playerLAtteck->GetPosX() >= MimWindowWidth) && (playerLAtteck->GetPosX() <= kWindowWidth)) {

					if (IsCollision(playerLAtteck, enemies) == true) {

						ChackEToPDicrection(enemies);

						float damege = playerLAtteck->GetAttackPoint();
						enemies->OnCollision(damege);
						playerLAtteck->OnCollision();


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

	if (nowWave_ == Boss) {
#pragma region プレイヤー攻撃とボス
		if (playerMA) {

			if (IsCollision(playerMA, apostelEvent_->GetObjectInfo()) == true) {

				float damege = playerMA->GetAttackPoint();
				apostelEvent_->OnCollision(damege);
			}
		}

		for (PlayerLAttack* playerLAtteck : playerLA) {

			if (playerLAtteck) {

				if (IsCollision(playerLAtteck, apostelEvent_->GetObjectInfo()) == true) {

					float damege = playerLAtteck->GetAttackPoint();
					apostelEvent_->OnCollision(damege);
					playerLAtteck->OnCollision();
				}
			}

		}

#pragma endregion

#pragma region プレイヤーとボス攻撃
		for (Apostel_MagicBall* magicBall : apostelEvent_->GetMagicBall()) {
			if (IsCollision(magicBall, player_) == true) {

				float damage = magicBall->GetAttackPoint();
				EnemyType enemytype = magicBall->GetAttributeType();
				player_->OnCollision(damage, enemytype);
				hitEffect_->OnColistion(enemytype);
			}

		}

		for (Apostel_ThrowMine* mine : apostelEvent_->GetThrowMine()) {
			if (mine->GetIsActive()) {
				if (IsCollision(mine, player_) == true) {

					float damage = mine->GetAttackPoint();
					EnemyType enemytype = mine->GetAttributeType();
					player_->OnCollision(damage, enemytype);
					hitEffect_->OnColistion(enemytype);
				}
			}

		}
#pragma endregion
	}

	if (nowWave_ == Wave3) {
#pragma region プレイヤー本体と浮遊敵

		for (FryingEnemy* enemies : fryingEnemy_) {

			if (IsCollision(player_, enemies) == true) {
				float damege = enemies->GetAttackPoint();
				EnemyType enemytype = enemies->GetEnemyType();
				player_->OnCollision(damege, enemytype);
				hitEffect_->OnColistion(enemytype);
				//enemies->AttackMotion();
			}
			//enemies;


		}
#pragma endregion 

#pragma region プレイヤー近距離と浮遊敵

		//わざと魔法でしか倒せない敵でも面白そう(ギミック追加したので没)
		if (playerMA) {
			for (FryingEnemy* enemies : fryingEnemy_) {

				if (IsCollision(playerMA, enemies) == true) {
					ChackEToPDicrection(enemies);

					float damege = playerMA->GetAttackPoint();
					enemies->OnCollision(damege);
				}

			}
		}
#pragma endregion

#pragma region プレイヤー遠距離と浮遊敵


		for (FryingEnemy* enemies : fryingEnemy_) {

			for (PlayerLAttack* playerLAtteck : playerLA) {

				if (playerLAtteck) {

					//画面外の物には反応しない
					if ((playerLAtteck->GetPosX() >= MimWindowWidth) && (playerLAtteck->GetPosX() <= kWindowWidth)) {

						if (IsCollision(playerLAtteck, enemies) == true) {

							ChackEToPDicrection(enemies);

							float damege = playerLAtteck->GetAttackPoint();
							enemies->OnCollision(damege);
							playerLAtteck->OnCollision();


						}
					}
				}

			}
#pragma endregion

		}


#pragma region 時間制限連続ダメージ

		for (FryingEnemy* enemies : fryingEnemy_) {


			float damege = enemies->GetContinuousDamage();
			int timer = enemies->GetDamageLimitTime();
			bool flag = enemies->GetDamageFrag();
			//フラグとダメージ数とタイマー
			player_->OnContinuousDamage(damege, timer, flag);
		}

#pragma endregion
	}
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
			int rum = RandomRange(4, 6);

			if (rum % 2 == 0) {

				PopItem* newItem = new PopItem();
				Vector2 pos = { enemies->GetPosX(), enemies->GetPosY() };
				newItem->Initialize(pos);

				popItem_.push_back(newItem);
			}
		}

		///チュートリアル用
		if ((tutrialSystem_->GetNowExprestion() == 2) && (enemies->GetIsDead() == true)) {
			tutrialSystem_->SetNowExprestion(3);
		}
		///チュートリアル用
		if ((tutrialSystem_->GetNowExprestion() == 4) && (enemies->GetIsDead() == true)) {
			tutrialSystem_->SetNowExprestion(5);
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

void GamePScene::FryingEnemyDead()
{

	for (FryingEnemy* enemies : fryingEnemy_) {
		if (enemies->GetIsDead()) {

			PopItem* newItem = new PopItem();
			Vector2 pos = { enemies->GetPosX(), enemies->GetPosY() };
			newItem->Initialize(pos);

			popItem_.push_back(newItem);
		}
	}

	fryingEnemy_.remove_if([](FryingEnemy* fryenemies) {
		if (fryenemies->GetIsDead()) {
			delete fryenemies;
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

void GamePScene::FryEnemyPoping()
{
	fryEnemyPopFrame_++;

	if (fryEnemyPopFrame_ >= consEnemyPopFrameFry_) {


		FryingEnemy* newEnemy = new FryingEnemy();

		newEnemy->Initialize(player_->GetMaindStateNow(), enemyNotAppeared_);
		enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
		fryingEnemy_.push_back(newEnemy);
		fryEnemyPopFrame_ = 0;

	}
}

void GamePScene::EnemyPoping(Wave& nowWave)
{

	//Waveg事に枠タイミングを分けている
	switch (nowWave)
	{
	case Tutorial:

		if ((tutrialSystem_->GetNowExprestion() == 2) && countEnemy_ == 0) {
			PopEnemy* newEnemy = new PopEnemy();

			newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
			enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
			enemy_.push_back(newEnemy);
			countEnemy_ = 1;
		}

		if ((tutrialSystem_->GetNowExprestion() == 4) && countEnemy_ == 1) {
			PopEnemy* newEnemy = new PopEnemy();

			newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
			enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
			enemy_.push_back(newEnemy);
			countEnemy_ = 2;
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
	case Boss:

		///SP回復の手助け(救済処置用に123の時より遅いペースで出現させるようにしている)
		//EnemyPopFrame_++;

		//if (EnemyPopFrame_ >= consEnemyPopFrameBoss_) {


		//	PopEnemy* newEnemy = new PopEnemy();
		//	newEnemy->Initialize(player_->GetMaindStateNow(), nowWave, enemyNotAppeared_);
		//	enemyNotAppeared_ = newEnemy->EnemyNotAppeared();
		//	enemy_.push_back(newEnemy);
		//	EnemyPopFrame_ = 0;

		//}
		break;

	default:
		break;
	}

}

void GamePScene::WaveChange()
{

	//右クリック押したら終わる
	if ((nowWave_ == Tutorial) && tutrialSystem_->GetIsDead()) {
		nowWave_ = Wave1;
		GameMove_ = false;
		/*timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);*/
		player_->SetSp(player_->GetSpMax());
		player_->SetHp(player_->GetHpMax());
		//ここにHpも作っておく
		waveTextUi_->Update(nowWave_);
		//wave変わった時に鳴らす奴

	}
	else if ((nowWave_ == Wave1) && (timerUi_->GetterTimer() <= 0)) {
		nowWave_ = Wave2;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);
		//wave変わった時に鳴らす奴
		waveTextUi_->WaveChangeMusic();
		waveTextUi_->Update(nowWave_);

	}
	else if ((nowWave_ == Wave2) && (timerUi_->GetterTimer() <= 0)) {
		nowWave_ = Wave3;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);
		//wave変わった時に鳴らす奴
		waveTextUi_->WaveChangeMusic();
		waveTextUi_->Update(nowWave_);
	}
	else if ((nowWave_ == Wave3) && (timerUi_->GetterTimer() <= 0)) {
		nowWave_ = Boss;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);
		//wave変わった時に鳴らす奴
		waveTextUi_->WaveChangeMusic();
		waveTextUi_->Update(nowWave_);
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
	else if ((nowWave_ == Wave3) && (!keys[DIK_0] && preKeys[DIK_0])) {
		nowWave_ = Boss;
		timerUi_->SetterTimer(timerMax);
		timerUi_->SetterMoveX(0);
		waveTextUi_->Update(nowWave_);

	}



#endif // _DEBUG

}

void GamePScene::AllStopMusic()
{
	for (PopEnemy* enemies : enemy_) {
		enemies->StopMusic();
	}

	player_->StopMusic();

	if (gameSModeNow_ == Pause) {
		bgm_->PauseBGM();
	}
	else {
		bgm_->StopBGM();
	}

}

void GamePScene::ChackNotAttack()
{
	if ((pouseMode_->GetNotAttackFrag() == false) && (tutrialSystem_->GetNotAttackFrag() == true)) {
		player_->SetNotAttackFrag(true);
	}
	else if ((pouseMode_->GetNotAttackFrag() == true) && (tutrialSystem_->GetNotAttackFrag() == false)) {
		player_->SetNotAttackFrag(true);
	}
	else if ((pouseMode_->GetNotAttackFrag() == false) && (tutrialSystem_->GetNotAttackFrag() == false)) {
		player_->SetNotAttackFrag(false);
	}
	else {
		player_->SetNotAttackFrag(true);
	}


	//player_->SetNotAttackFrag(true);
}

///没(使わなくなった)
void GamePScene::ChackEToPDicrection(EnemyBase* enemy)
{
	if (player_->GetPosX() >= enemy->GetPosX()) {
		enemy->SetBaseMoveX(-(enemy->GetkBaseMoveX_()));
	}
	else {
		enemy->SetBaseMoveX(enemy->GetkBaseMoveX_());
	}

}

