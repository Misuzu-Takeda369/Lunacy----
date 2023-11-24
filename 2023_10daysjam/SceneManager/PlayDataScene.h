#pragma once
#include "SaveData.h"
#include "Function/UtilityStruct.h"
class PlayDataScene
{
public:
	void Initialize();
	void Update();
	void SetSaveData(SaveData* data);
	void Draw();
	void SetSceneChangeFlag(bool flag) { backTitleFlag = flag; }
	bool GetSceneChangeFlag() { return backTitleFlag; }
private:
	void MouseBottonChack();
	SaveData* data_;

	IntState mousePos_ = { 0,0 };
	bool backTitleFlag = false;
	unsigned int backTitleButton_;
	IntState backButtonPos_ = { 20,580 };
	int buttonSize_ = int(512 * 0.25);
};

//要るかどうかというと別に…(・∀・)