#include "MousePointer.h"


//Novice::SetMouseCursorVisibility(visibility);

MousePointer::MousePointer()
{
}

MousePointer::~MousePointer()
{
}

void MousePointer::Initialize()
{
	mousePos_ = { 0,0 };

	pointerImage_ = Novice::LoadTexture("./Resources/images/UI/mousepointer_kari.png");
}

void MousePointer::Update()
{
	Novice::SetMouseCursorVisibility(0);

	Novice::GetMousePosition(&mousePos_.x_, &mousePos_.y_);
}

void MousePointer::Draw()
{
	Novice::DrawSprite(mousePos_.x_ - (pointerSize.x_/2), mousePos_.y_ - (pointerSize.y_ / 2), pointerImage_,1,1,0.0f,WHITE);
}
