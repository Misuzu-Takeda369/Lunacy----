#include "SaveData.h"
#include <fstream>
#include <assert.h>

void SaveData::Initialize()
{
	LoadData();
	GetWaveData();
	GetTimeData();

}

void SaveData::OnResultUpdate(const int& wave)
{
	//クリア時に上書き(しないほうがトピックに合う気がする最高waveも見せつけられるので)
	//if ((lastWave_ < wave) || (wave == 0)) {
	//	lastWave_ = wave;
	//	WriteData();
	//}
	if (lastWave_ < wave) {
		lastWave_ = wave;
		WriteData();
	}

}

void SaveData::Update()
{
	playFrame_++;
	if (playFrame_ >= 60) {
		playSecond_++;
		playFrame_ = 0;
	}
	if (playSecond_ >= 60) {
		playMin_++;
		playSecond_ = 0;
	}
	if (playMin_ >= 60) {
		playHour_++;
		playMin_ = 0;
	}
#ifdef _DEBUG
	//WriteData();
#endif // _DEBUG
}

void SaveData::OnBeforeCloseUpdate()
{
	WriteData();
}

void SaveData::LoadData()
{
	std::ifstream readFile;
	readFile.open("data/save");
	assert(readFile.is_open());
	datas_ << readFile.rdbuf();
	readFile.close();
}

void SaveData::GetWaveData()
{
	std::string line;
	while (std::getline(datas_, line)) {
		std::istringstream istr(line);
		std::string key;

		getline(istr, key, ',');
		if (key.find("//") == 0) {
			continue;
		}
		if (key.find("wave") == 0) {
			getline(istr, key, ',');
			lastWave_ = (int)std::atoi(key.c_str());
			break;
		}
	}
}

void SaveData::GetTimeData()
{
	std::string line;
	while (std::getline(datas_, line)) {
		std::istringstream istr(line);
		std::string key;

		getline(istr, key, ',');
		if (key.find("//") == 0) {
			continue;
		}
		if (key.find("frame") == 0) {
			getline(istr, key, ',');
			playFrame_ = (int)std::atoi(key.c_str());
		}
		else if (key.find("sec") == 0) {
			getline(istr, key, ',');
			playSecond_ = (int)std::atoi(key.c_str());
		}
		else if (key.find("min") == 0) {
			getline(istr, key, ',');
			playMin_ = (int)std::atoi(key.c_str());
		}
		else if (key.find("hour") == 0) {
			getline(istr, key, ',');
			playHour_ = (int)std::atoi(key.c_str());
			break;
		}
	}
}

void SaveData::WriteData()
{
	std::ofstream writeFile;
	writeFile.open("data/save");
	writeFile << "wave," << lastWave_ <<","<< std::endl;
	writeFile << "frame," << playFrame_ << "," << std::endl;
	writeFile << "sec," << playSecond_ << "," << std::endl;
	writeFile << "min," << playMin_ << "," << std::endl;
	writeFile << "hour," << playHour_ << "," << std::endl;
	writeFile.close();
}

