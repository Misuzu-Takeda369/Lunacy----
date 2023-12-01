#include "NSEnemy.h"


NSEnemy::~NSEnemy()
{
	delete animation_;
}

void NSEnemy::Initialize(Vector2 pos, Vector2 speed, float radius)
{
	charaBase_.pos_ = pos;
	charaBase_.speed_ = speed;
	charaBase_.radius_ = radius;
	charaBase_.color_ = BLUE;


	hp_ = maxHp_;

	lunaticPoint_ = 10.0f * 2;

	//プレイヤーに影響する攻撃力
	attackPoint_ = lunaticPoint_;


	//敵が死んでいるか
	isDead_ = false;

	//敵が移動した量
	moveEnemy_ = { 0.0f,0.0f };

	////アニメーション初期化(元)
	/*animation_ = new Enemy1Anim;
	animation_->Initialize();*/
	//アニメーション初期化
	animation_ = new BladeSlimeAnimS();
	animation_->Initialize();
}

void NSEnemy::Update()
{

	//敵の移動
	Move();

	NaturalDeath();

	//アニメーションUpdate
	animation_->Update(charaBase_.pos_);
	animation_->SetDirection(_right);
	animation_->SetMaindState(Lunatic);

}

void NSEnemy::Draw()
{
#ifdef _DEBUG
	Novice::DrawEllipse(int(charaBase_.pos_.x), int(charaBase_.pos_.y), int(charaBase_.radius_), int(charaBase_.radius_), 0.0f, charaBase_.color_, kFillModeSolid);
#endif
	//アニメーションDraw
	animation_->Draw(charaBase_.color_);
	

}
