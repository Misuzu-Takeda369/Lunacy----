#include "DummyObject.h"
void DummyObject::Initialize(CharaBase base)
{
	charaBase_ = base;
	collisionType_ = Circle;
	boxSize_ = { 30.f,50.f };
	charaBase_.radius_ = 30.f;
}
