#include "WaveSelect.h"

WaveSelect::WaveSelect()
{
}

WaveSelect::~WaveSelect()
{
}

void WaveSelect::Initialize()
{
	mousePos_ = { 0,0 };

	changeTimingFrame_ = 0;

	nowWave_ = Tutorial;

	maxWave_ = Tutorial;
}

void WaveSelect::Initialize(Wave& maxWave)
{
	mousePos_ = { 0,0 };

	changeTimingFrame_ = 0;

	nowWave_ = Tutorial;
	maxWave_ = maxWave;
}

void WaveSelect::Update()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	changeTimingFrame_++;

#ifdef _DEBUG

	//現在は1を押したときに移動
	if ((preKeys[DIK_I] == 0 && keys[DIK_I] != 0) && changeTimingFrame_ >= changeTimingFrameMax_) {
		flagChange_ = true;
		changeTimingFrame_ = 0;
	}

#endif // _DEBUG

}

void WaveSelect::Draw()
{
}

void WaveSelect::MouseBottonChack()
{
	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);

}
