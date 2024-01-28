#include "SceneManager.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {
	// それぞれデリート
	delete title_;
	delete gameP_;
	delete gameC_;
	delete gameO_;
	delete waveS_;
	delete saveData_;

	delete changing_;
}

void SceneManager::Initialize() {

	//シーン番号の初期化
	sceneNum_ = TitleMode;

	memcpy(preKeys, preKeys, 256);
	Novice::GetHitKeyStateAll(keys);


	//インスタンス作成
	title_ = new TitleScene();
	gameP_ = new GamePScene();
	gameC_ = new GameCScene();
	gameO_ = new GameOScene();
	waveS_ = new WaveSelect();

	saveData_ = new SaveData;
	dataScene_ = new PlayDataScene;

	//初期化
	title_->Initialize();
	gameP_->Initialize(nowWave_);
	gameC_->Initialize();
	gameO_->Initialize();
	waveS_->Initialize(maxWave_);

	saveData_->Initialize();
	dataScene_->Initialize();

	nowWave_ = Tutorial;
	maxWave_ = Tutorial;
	//maxWave_ = saveData_->GetLastWave();
	//nowWave_ = Wave(maxWave_);

	changing_ = new SceneChangeEase();
	changing_->Initialize();

}

void SceneManager::Update() {

	saveData_->Update();
	// シーン毎の更新
	switch (sceneNum_) {

	case TitleMode:

		if (changing_->GetNowEffectMode() == After) {
			changing_->ChangeAfter();
		}
		else if (changing_->GetNowEffectMode() == Nochange) {
			title_->SetMaxWave(maxWave_);
			title_->Update();
		}

		//シーン変換
		//タイトルのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//ゲームプレイモードに移行する
		if (title_->GetFlagChange()) {

			//変更フラグを受け取った時
			changing_->SetNowEffectMode(Before);
			changing_->ChangeBefore();
			//シーンが変わるとき

			if (changing_->GetNowEffectMode() == After) {


				//初めて起動したときorもしくはクリア画面を見た場合
				if (maxWave_ == Tutorial) {
					sceneNum_ = GPlayMode;
					gameP_ = new GamePScene();
					nowWave_ = Tutorial;
					gameP_->Initialize(nowWave_);
					title_->SetFlagChange(false);
					

				}
				else if ((maxWave_ != Tutorial) && (title_->GetOnReset() == true)) {
					sceneNum_ = GPlayMode;
					gameP_ = new GamePScene();
					nowWave_ = Tutorial;
					maxWave_ = Tutorial;
					gameP_->Initialize(nowWave_);
					title_->SetFlagChange(false);

					
				}
				else {

					//それ以降
					sceneNum_ = WaveSelectMode;
					title_->SetFlagChange(false);


					title_ = new TitleScene();
					title_->Initialize();

					//deleteとnewと初期化(初期化だけでもよさそう感)
					//動きによっては別な場所へ
					waveS_ = new WaveSelect();
					waveS_->Initialize(maxWave_);

				}
			}

		}

		if (title_->GetToPlayDataFlag()) {

			//変更フラグを受け取った時
			changing_->SetNowEffectMode(Before);
			changing_->ChangeBefore();
			//変更フラグを受け取った時

			if (changing_->GetNowEffectMode() == After) {

				sceneNum_ = PlayDataMode;
				title_->SetToPlayDataFlag(false);
				dataScene_->SetSaveData(saveData_);
				int num = RandomRange(0, dataScene_->GetMaxTips());
				dataScene_->SetTips(num);
			}

		}
		break;

	case WaveSelectMode:

		if (changing_->GetNowEffectMode() == After) {
			changing_->ChangeAfter();
		}
		else if (changing_->GetNowEffectMode() == Nochange) {
			waveS_->Update();
		}


		if (waveS_->GetFlagChange()) {

			//変更フラグを受け取った時
			changing_->SetNowEffectMode(Before);
			changing_->ChangeBefore();

			if (changing_->GetNowEffectMode() == After) {

				if (waveS_->GetTitleChangeFlag()) {

					sceneNum_ = TitleMode;
					waveS_->SetFlagChange(false);

				}
				else {

					sceneNum_ = GPlayMode;
					waveS_->SetFlagChange(false);


					//現在のwaveを受け取る
					nowWave_ = waveS_->GetNowWave();
					//deleteとnewと初期化(初期化だけでもよさそう感)
					//動きによっては別な場所へ
					gameP_ = new GamePScene();
					gameP_->Initialize(nowWave_);

				}
			}

		}

		break;

	case GPlayMode:

		if (changing_->GetNowEffectMode() == After) {
			changing_->ChangeAfter();
		}
		else if (changing_->GetNowEffectMode() == Nochange) {
			gameP_->Update();
		}

	

		//シーン変換
		//プレイモードのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameP_->GetFlagChange()) {

			//変更フラグを受け取った時
			changing_->SetNowEffectMode(Before);
			changing_->ChangeBefore();
			//変更フラグを受け取った時

			if (changing_->GetNowEffectMode() == After) {

				//現在のwaveを受け取る
				nowWave_ = gameP_->GetNowWave();
				if (maxWave_ < nowWave_) {
					maxWave_ = nowWave_;
				}

				if (gameP_->GetFlagGameOver()) {
					sceneNum_ = GOverMode;

					int Set = maxWave_;
					if (maxWave_ != Tutorial) {
						Set = maxWave_ - 1;
					}
					saveData_->OnResultUpdate((Set));
				}
				//ここにポーズからタイトル戻れるようにする
				else if (gameP_->GetFlagTitle()) {
					sceneNum_ = TitleMode;

					int Set = maxWave_;
					if (maxWave_ != Tutorial) {
						Set = maxWave_ - 1;
					}
					saveData_->OnResultUpdate((Set));
				}
				else {
					sceneNum_ = GClearMode;
				}


				gameP_->SetFlagChange(false);

			}

		}
		break;

	case GClearMode:

		if (changing_->GetNowEffectMode() == After) {
			changing_->ChangeAfter();
		}
		else if (changing_->GetNowEffectMode() == Nochange) {
			gameC_->Update();
		}
		//シーン変換
		

		//クリアシーンのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameC_->GetFlagChange()) {

			//変更フラグを受け取った時
			changing_->SetNowEffectMode(Before);
			changing_->ChangeBefore();
			//変更フラグを受け取った時

			if (changing_->GetNowEffectMode() == After) {
				

				sceneNum_ = TitleMode;
				gameC_->SetFlagChange(false);
				//deleteとnewと初期化(初期化だけでもよさそう感)
				//動きによっては別な場所へ


				
				saveData_->OnResultUpdate(maxWave_);
				//クリアするとリセットする
				maxWave_ = Tutorial;

				gameC_ = new GameCScene();
				gameC_->Initialize();
			}
		}
		break;

	case GOverMode:

		if (changing_->GetNowEffectMode() == After) {
			changing_->ChangeAfter();
		}
		else if (changing_->GetNowEffectMode() == Nochange) {
			gameO_->Update();
		}

		//シーン変換
		//オーバーシーンのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameO_->GetFlagChange()) {

			//変更フラグを受け取った時
			changing_->SetNowEffectMode(Before);
			changing_->ChangeBefore();
			//変更フラグを受け取った時

			if (changing_->GetNowEffectMode() == After) {


				if (gameO_->GetFlagRetry()) {
					sceneNum_ = GPlayMode;
				}
				else {
					sceneNum_ = TitleMode;
					gameO_->SetFlagChange(false);
				}


				//deleteとnewと初期化(初期化だけでもよさそう感)
				//動きによっては別な場所へ

				gameO_ = new GameOScene();
				gameO_->Initialize();
				//deleteとnewと初期化(初期化だけでもよさそう感)
				//動きによっては別な場所へ
				gameP_ = new GamePScene();
				gameP_->Initialize(nowWave_);
			}
		}
		break;

	case PlayDataMode:

		if (changing_->GetNowEffectMode() == After) {
			changing_->ChangeAfter();
		}
		else if (changing_->GetNowEffectMode() == Nochange) {
			dataScene_->SetSaveData(saveData_);
			dataScene_->Update();
		}

		if (dataScene_->GetSceneChangeFlag()) {

			//変更フラグを受け取った時
			changing_->SetNowEffectMode(Before);
			changing_->ChangeBefore();
			//変更フラグを受け取った時


			if (changing_->GetNowEffectMode() == After) {
				sceneNum_ = TitleMode;
				dataScene_->SetSceneChangeFlag(false);
			}
		}

		break;
	default:

		break;
	}

#ifdef _DEBUG
#pragma region ImGui関連

	ImGui::Begin("SceneModeCheck");
	ImGui::Text("sceneNum_ %d\nNextScene[DIK_I] GameOver&Retry[DIK_O]", sceneNum_);
	ImGui::End();

	ImGui::Begin("SaveDataCheck");
	ImGui::Text("wave:%d", saveData_->GetWave());
	ImGui::Text("PlayTime %02d:%02d:%02d", saveData_->GetPlayHour(), saveData_->GetPlayMin(), saveData_->GetPlaySecond());
	ImGui::End();

#pragma endregion
#endif // DEBUG

}

void SceneManager::Draw() {

	// シーン毎の描写
	switch (sceneNum_) {

	case TitleMode:
		title_->Draw();



		break;

	case WaveSelectMode:

		waveS_->Draw();


		break;

	case GPlayMode:
		gameP_->Draw();

		break;

	case GClearMode:
		gameC_->Draw();

		break;

	case GOverMode:
		gameO_->Draw();

		break;

	case PlayDataMode:
		dataScene_->Draw();

	default:
		break;
	}

	changing_->Draw();
}

