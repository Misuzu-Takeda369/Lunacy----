#include "BGMManage.h"

void BGMManage::Initialize()
{
	nomalBGM_ = Novice::LoadAudio("./Resources/Music/BGM/rimeikudesu.wav");
	bossBGM_ = Novice::LoadAudio("./Resources/Music/BGM/melancholic_syndrome.wav");
	dangerBGM_ = Novice::LoadAudio("./Resources/Music/BGM/Monaxia_Cruel_Daughter.wav");


	nomalPlay_ = -1;
	bossPlay_ = -1;
	dangerPlay_ = -1;

}

void BGMManage::Update(float& Hp, float& Sp, Wave& NowWave)
{

	if ((Hp < ChangeBGM) && (Sp < ChangeBGM)) {

		//曲が成っていた場合は止める
		if ((Novice::IsPlayingAudio(nomalPlay_) == 1)) {
			Novice::PauseAudio(nomalPlay_);
		}
		//曲が成っていた場合は止める
		if ((Novice::IsPlayingAudio(bossPlay_) == 1)) {
			Novice::PauseAudio(bossPlay_);
		}

		if ((Novice::IsPlayingAudio(dangerPlay_) == 0) && (dangerPlay_ = -1)) {
			//念のためisplayつかっとく
			dangerPlay_ = Novice::PlayAudio(dangerBGM_, 1, 0.4f);
		}
		else {
			Novice::ResumeAudio(dangerPlay_);
		}

	}
	else {

		if ((NowWave != Tutorial) && (NowWave != Boss)) {

			//曲が成っていた場合は止める
			if ((Novice::IsPlayingAudio(dangerPlay_) == 1)) {
				Novice::PauseAudio(dangerPlay_);
			}


			if ((Novice::IsPlayingAudio(nomalPlay_) == 0) && (nomalPlay_ = -1)) {
				//念のためisplayつかっとく
				nomalPlay_ = Novice::PlayAudio(nomalBGM_, 1, 0.8f);
			}
			else {
				Novice::ResumeAudio(nomalPlay_);
			}


		}
		else if (NowWave == Boss) {

			Novice::StopAudio(nomalPlay_);

			//曲が成っていた場合は止める
			if ((Novice::IsPlayingAudio(dangerPlay_) == 1)) {
				Novice::PauseAudio(dangerPlay_);
			}


			if ((Novice::IsPlayingAudio(bossPlay_) == 0) && (bossPlay_ = -1)) {
				//念のためisplayつかっとく
				bossPlay_ = Novice::PlayAudio(bossBGM_, 1, 0.4f);
			}
			else {
				Novice::ResumeAudio(bossPlay_);
			}


		}
		else {
			//チュートリアル中はBGM流さない方針(もしくは別な奴か同じ奴流すか)
		}
	}
}

void BGMManage::StopBGM()
{
	Novice::StopAudio(nomalPlay_);
	Novice::StopAudio(bossPlay_);
	Novice::StopAudio(dangerPlay_);
}

void BGMManage::PauseBGM()
{
	Novice::PauseAudio(nomalPlay_);
	Novice::PauseAudio(bossPlay_);
	Novice::PauseAudio(dangerPlay_);
}

