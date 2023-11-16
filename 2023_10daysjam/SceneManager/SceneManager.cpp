#include "SceneManager.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {
	// それぞれデリート
	delete title_;
	delete gameP_;
	delete gameC_;
	delete gameO_;
	delete waveS_;
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

	//初期化
	title_->Initialize();
	gameP_->Initialize();
	gameC_->Initialize();
	gameO_->Initialize();
	waveS_->Initialize();

}

void SceneManager::Update() {

	// シーン毎の更新
	switch (sceneNum_) {

	case TitleMode:

		title_->Update();

		//シーン変換
		//タイトルのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//ゲームプレイモードに移行する
		if (title_->GetFlagChange()) {
			sceneNum_ = WaveSelectMode;
			title_->SetFlagChange(false);

			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ
			title_ = new TitleScene();
			title_->Initialize();
		}
		break;

	case WaveSelectMode:

		waveS_->Update();

		if (waveS_->GetFlagChange()) {
			sceneNum_ = GPlayMode;
			waveS_->SetFlagChange(false);

			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ
			waveS_ = new WaveSelect();
			waveS_->Initialize();
		}

		break;

	case GPlayMode:
		gameP_->Update();

		//シーン変換
		//プレイモードのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameP_->GetFlagChange()) {
			if (gameP_->GetFlagGameOver()) {
				sceneNum_ = GOverMode;
			}
			else {
				sceneNum_ = GClearMode;
			}
			gameP_->SetFlagChange(false);


			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ
			gameP_ = new GamePScene();
			gameP_->Initialize();
		}
		break;

	case GClearMode:
		gameC_->Update();

		//シーン変換
		//クリアシーンのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameC_->GetFlagChange()) {
			sceneNum_ = TitleMode;
			gameC_->SetFlagChange(false);

			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ
			gameC_ = new GameCScene();
			gameC_->Initialize();
		}
		break;

	case GOverMode:
		gameO_->Update();

		//シーン変換
		//オーバーシーンのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameO_->GetFlagChange()) {

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

	default:
		break;
	}
}

