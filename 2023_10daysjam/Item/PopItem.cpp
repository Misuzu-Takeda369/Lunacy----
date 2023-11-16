#include "PopItem.h"

PopItem::~PopItem()
{
	delete spRecoverItem_;
}

void PopItem::Initialize(Vector2& pos)
{

	run_ = 1;
	popItem_ = SpRecover;
	recoverState_ = 0.0f;

	collisionType_ = Circle;

#pragma region ポップした時の判別
	run_ = RandomRange(1, 1);
	if (run_ == 1) {
		popItem_ = SpRecover;
	}
	else if (run_ == 2) {
		popItem_ = HpRecover;
	}

	switch (popItem_)
	{
	case SpRecover:

		spRecoverItem_ = new SpRecoverItem();
		spRecoverItem_->Initialize(pos);

		break;

	case HpRecover:

		break;

	default:
		break;
	}
#pragma endregion

}

void PopItem::Update()
{
	switch (popItem_)
	{
	case SpRecover:

		if (isDead_ == false) {
			spRecoverItem_->Update();
			charaBase_.pos_.x = spRecoverItem_->GetPosX();
			charaBase_.pos_.y = spRecoverItem_->GetPosY();
			charaBase_.radius_ = spRecoverItem_->GetRadish();
			recoverState_ = spRecoverItem_->GetRecoverSp();
		}

		if (spRecoverItem_->IsDead()) {
			isDead_ = true;
		}

		break;

	case HpRecover:

		break;

	default:
		break;
	}

#ifdef _DEBUG
#pragma region ImGui関連

	ImGui::Begin("Item");
	ImGui::Text("ItemPos:%f,%f\n", charaBase_.pos_.x, charaBase_.pos_.y);
	ImGui::End();


#pragma endregion
#endif // DEBUG

}

void PopItem::Draw()
{
	switch (popItem_)
	{
	case SpRecover:

		if (isDead_ == false) {
			spRecoverItem_->Draw();
		}

		break;

	case HpRecover:

		break;

	default:
		break;
	}
}

void PopItem::OnColistion()
{
	//ここにエフェクト関連
	isDead_ = true;
}

