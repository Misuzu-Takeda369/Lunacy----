#include "EnemyBase.h"



void EnemyBase::Initialize(Vector2 pos, Vector2 speed, float radius)
{
	pos; speed; radius;
}

void EnemyBase::Update()
{

}

void EnemyBase::Draw()
{
}

void EnemyBase::Move()
{
	charaBase_.pos_.x -= charaBase_.speed_.x;
	moveEnemy_.x -= charaBase_.speed_.x;
}

void EnemyBase::NaturalDeath()
{
	if (moveEnemy_.x <= -1500.0f) {
		isDead_ = true;
		//moveEnemy_.x <= 1400.0f;
	}
	else if(moveEnemy_.x >= 1500.0f){
		isDead_ = true;
	}
}

void EnemyBase::OnCollision(float& damege)
{
	damege;
}

void EnemyBase::OncollBackMove(float m)
{
	BaseMoveX_ = m;

	//スピードの判定
	if (BaseMoveX_ >= 0) {
		BackSpeedX_ = kBackSpeedX_;
	}
	else {
		BackSpeedX_ = -kBackSpeedX_;
	}

	//移動判定
	if ((MoveX_ < BaseMoveX_) && (BackSpeedX_ > 0)) {

		//移動量リセット
		if (MoveX_ < 0) {
			MoveX_ = 0;
		}

		MoveX_ += BackSpeedX_;
		charaBase_.pos_.x += MoveX_;
	}
	else if ((MoveX_ > BaseMoveX_) && (BackSpeedX_ < 0)) {

		//移動量リセット
		if (MoveX_ > 0) {
			MoveX_ = 0;
		}

		MoveX_ += BackSpeedX_;
		charaBase_.pos_.x += MoveX_;
	}
	else {
		MoveX_ = BaseMoveX_;
		charaBase_.pos_.x = charaBase_.pos_.x +  MoveX_;
	}
	
}

void EnemyBase::OncollEffect()
{

}

void EnemyBase::DeadEnemyEffect()
{
}

void EnemyBase::AttackMotion()
{
}

void EnemyBase::AttackCool()
{
}


