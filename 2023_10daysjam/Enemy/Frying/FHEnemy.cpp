#include "FHEnemy.h"

FHEnemy::~FHEnemy()
{
	delete flyeye_;
}

void FHEnemy::Initialize(Vector2 pos, Vector2 speed, float radius)
{
	charaBase_.pos_ = pos;
	charaBase_.speed_ = speed;
	charaBase_.radius_ = radius;
	charaBase_.color_ = RED;

	//縦の移動(移動の中心地)
	center = 0.0f;
	//角度
	theta = 0.0f;
	//グラフ？何倍か(基準が1なので)
	ampli = 3.0f;

	hp_ = maxHp_;

	//プレイヤーに影響する攻撃力
	attackPoint_ = nomalPoint_;


	isDead_ = false;

	//敵が移動した量
	moveEnemy_ = { 0.0f,0.0f };

	//アニメーション初期化
	flyeye_ = new FlyEye();
	flyeye_->Initialize();
}

void FHEnemy::Update()
{
	Move();
	//敵の自然死
	NaturalDeath();
	flyeye_->Update(charaBase_.pos_);
	flyeye_->SetDirection(_right);
	
}

void FHEnemy::Draw()
{
#ifdef _DEBUG
	Novice::DrawEllipse(int(charaBase_.pos_.x), int(charaBase_.pos_.y), int(charaBase_.radius_), int(charaBase_.radius_), 0.0f, charaBase_.color_, kFillModeSolid);
#endif
	flyeye_->Draw(WHITE);
}

void FHEnemy::Move()
{
	theta += float(M_PI / 30.0f);
	charaBase_.pos_.y +=  (cosf(theta) * ampli);
	charaBase_.pos_.x -= charaBase_.speed_.x;

	
}
