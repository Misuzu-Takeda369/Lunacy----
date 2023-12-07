#include "Apostel.h"
#include <cmath>
#include "Function/Function.h"
#include "ScreenSize.h"

Apostel::~Apostel()
{
	delete anim_;
	delete hpUI_;
	for (Apostel_MagicBall* magicBall : magicBall_) {
		delete magicBall;
	}
}

void Apostel::Initialize(Vector2 pos, Vector2 speed, float radius)
{
	charaBase_.pos_ = pos;
	charaBase_.pos_ = { 1200.f,300.f };
	charaBase_.speed_ = speed;
	charaBase_.radius_ = radius;
	charaBase_.color_ = WHITE;
	hp_ = maxHP_;
	isDead_ = false;
	anim_ = new ApostelAnim;
	anim_->Initialize();
	isDead_ = false;
	collisionType_ = Box;
	boxSize_ = { 256.f * 0.25f,512.f * 0.25f };
	hpUI_ = new EHpUI;
	hpUI_->Initialize(charaBase_.pos_);
	hitCoolTime_ = 0;
	center_ = charaBase_.pos_;
	flowingTheta_ = 0;
}

void Apostel::Update()
{
	switch (phase_)
	{
	case Apostel::first:
		Phase_First();
		if (hp_ <= maxHP_ * 0.5f) {
			phase_ = second; //HP50%以下でフェーズ2に移行
			state_ = IDOL;
		}
		break;
	case Apostel::second:
		Phase_Second();
		if (hp_ <= maxHP_ * 0.25f) {
			phase_ =third; //HP25%以下でフェーズ3に移行
		}
		break;
	case Apostel::third:
		if (hp_ <= 0.0f) {
			phase_ = dead; //HP0%以下で死亡状態に移行
		}
		break;
	case Apostel::dead:
		break;
	default:
		break;
	}
	anim_->Update(charaBase_.pos_);
	anim_->SetDirection(_right);
	anim_->SetState(state_);
	hpUI_->Update(hp_, charaBase_.pos_);
	CoolCheak();

	//端制限
	if (charaBase_.pos_.x <= MimWindowWidth + boxSize_.x) {
		charaBase_.pos_.x = MimWindowWidth + boxSize_.x;
		moveDirection_ = 1;//移動方向反転
		_right = true;
	}
	if (charaBase_.pos_.x >= kWindowWidth - boxSize_.x) {
		charaBase_.pos_.x = kWindowWidth - boxSize_.x;
		moveDirection_ = -1;//移動方向反転
		_right = false;
	}
	UpdateProjectile();
}

void Apostel::Draw()
{
	DrawProjectile();
	Novice::DrawBox(int(charaBase_.pos_.x - (boxSize_.x / 2.f)),int(charaBase_.pos_.y - (boxSize_.y / 2.f)),
		int(boxSize_.x),int( boxSize_.y), 0, WHITE, kFillModeWireFrame);
	anim_->Draw(charaBase_.color_);
	hpUI_->Draw();
	
}

void Apostel::Move()
{
}

void Apostel::NaturalDeath()
{
	0;
}

void Apostel::OnCollision(float& damege)
{
	if (!hit_) {
		hp_ -= damege;
		hit_ = true;
	}

	if (hp_ <= 0.0f) {
		hp_ = 0;
		//isDead_ = true;
	}
}

void Apostel::SetPlayerBase(CharaBase player)
{
	playerBase_ = player;
}

void Apostel::Phase_First()
{
	flowingTheta_ -= 0.05f;
	center_ = charaBase_.pos_;
	charaBase_.pos_.y = (1.f * std::cosf(flowingTheta_) + 2.f * std::sinf(flowingTheta_))+center_.y;
	
	magicBallCoolTimeCounter_--;
	switch (state_)
	{
	case IDOL:
		actChangeTime_++;
		if (actChangeTime_ >= 60) {
			int num = RandomRange(1, 10);
			if (num > 5) {
				state_ = MOVE;
				//移動方向の決定
				int num2 = RandomRange(1, 10);
				if (num2 > 5) {
					moveDirection_ = 1;
					_right = true;
				}
				else {
					moveDirection_ = -1;
					_right = false;
				}
			}
			else {
				state_ = ATTACK;
			}
			actChangeTime_ = 0;
		}
		break;
	case MOVE:
		actChangeTime_++;
		charaBase_.pos_.x += 5*moveDirection_;
		if (1) {
			int num = RandomRange(1, 25);
			if (actChangeTime_ >= 40 + num) {
				int num2 = RandomRange(1, 8);
				if (num2 < 5) {
					state_ = IDOL;
				}
				else if (num2 > 3) {
					state_ = ATTACK;
				}
				actChangeTime_ = 0;
				int num3 = RandomRange(1, 10);
				if (num3 > 5) {
					moveDirection_ = 1;
					_right = true;
				}
				else {
					moveDirection_ = -1;
					_right = false;
				}
			}
		}
		break;
	case DEAD:
		break;
	case ATTACK:
		if (magicBallCoolTimeCounter_ <= 0) {
			Apostel_MagicBall* newMagicBall = new Apostel_MagicBall;
			newMagicBall->Initialize(charaBase_);
			_right = newMagicBall->GetDirection();
			magicBall_.push_back(newMagicBall);
			magicBallCoolTimeCounter_ = magicBallCoolTime_ + RandomRange(-20, 60);
		}
		actChangeTime_++;
		if (1) {
			int num = RandomRange(20, 60);
			if (actChangeTime_ >= 60 + num) {
				state_ = IDOL;
				actChangeTime_ = 0;
			}
		}

		break;
	case SKILL:
		break;
	default:
		break;
	}
	
}

void Apostel::Phase_Second()
{
	magicBallCoolTimeCounter_--;
	switch (state_)
	{
	case IDOL:
		break;
	case MOVE:
		break;
	case JUMP:
		break;
	case DEAD:
		break;
	case ATTACK:
		break;
	case SKILL:
		break;
	case SPECIAL:
		break;
	default:
		break;
	}
}

void Apostel::Phase_Third()
{
}

void Apostel::CoolCheak()
{
	if (hit_) {
		hitCoolTime_++;

		if (hitCoolTime_ >= MaxHitCoolTime_) {
			hit_ = false;
			hitCoolTime_ = 0;
		}
	}
}

void Apostel::DrawProjectile()
{
	for (Apostel_MagicBall* magicBall : magicBall_) {

		magicBall->Draw();
	}
}

void Apostel::UpdateProjectile()
{
	for (Apostel_MagicBall* magicBall : magicBall_) {

		magicBall->Update();
	}
}

void Apostel::DeleteProjectile()
{
	magicBall_.remove_if([](Apostel_MagicBall* magicBall) {
		if (magicBall->IsDead()) {
			delete magicBall;
			return true;
		}

		return false;
		});
}
