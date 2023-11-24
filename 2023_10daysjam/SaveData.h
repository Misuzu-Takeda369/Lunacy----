#pragma once
#include <sstream>
class SaveData
{
	//仮
public:
	void Initialize();
	void OnResultUpdate(const int& wave); //リザルト画面で更新する
	void Update();
	void OnBeforeCloseUpdate(); //ゲームを閉じる前に更新
	int GetWave() { return lastWave_; }
	int GetPlayHour() { return playHour_; }
	int GetPlayMin() { return playMin_; }
	int GetPlaySecond() { return playSecond_; }
protected:
	void LoadData();
	void GetWaveData();
	void GetTimeData();
	void WriteData();
	std::stringstream datas_;
	int lastWave_;
	int checkPointWave_;

	int playFrame_; //フレームカウント
	int playSecond_;//秒カウント
	int playMin_;   //分カウント
	int playHour_;  //時間カウント
};

