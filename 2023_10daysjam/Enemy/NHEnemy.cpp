#include"NHEnemy.h"

void NHEnemy::Initialize(Vector2 pos, Vector2 speed, float radius)
{
	charaBase_.pos_ = pos;
	charaBase_.speed_ = speed;
	charaBase_.radius_ = radius;
	charaBase_.color_ = RED;


	hp_ = maxHp_;

	//プレイヤーに影響する攻撃力
	attackPoint_ = nomalPoint_;


	//敵が死んでいるか
	isDead_ = false;

	//敵が移動した量
	moveEnemy_ = { 0.0f,0.0f };

	//アニメーション初期化
	animation_ = new Enemy1Anim;
	animation_->Initialize();

}

void NHEnemy::Update()
{
	/*
	//敵の移動
	for (int i = 0; i < ENEMY_MAX; i++) {
		enemyPos[i].x -= enemySpeed;

		//敵の攻撃
		if (E_Bullet->enemy_isShot == false) {
			E_Bullet->enemy_isShot = true;
			E_Bullet->bulletPos.x = enemyPos[i].x - enemyRadius;
			E_Bullet->bulletPos.y = enemyPos[i].y;
		}
	}

	if (E_Bullet->enemy_isShot == true) {
		E_Bullet->bulletPos.x -= E_Bullet->bulletSpeed;
	}

	if (E_Bullet->bulletPos.x <= E_Bullet->bulletRadius) {
		E_Bullet->enemy_isShot = false;
	}

	if (enemyHp == 0) {
		E_Bullet->enemy_isShot = false;
	}

	*/

	//敵の移動
	Move();

	//敵の自然死
	NaturalDeath();


	//アニメーションUpdate
	animation_->Update(charaBase_.pos_);
	


#ifdef _DEBUG
#pragma region ImGui関連

	ImGui::Begin("Enemy");
	ImGui::Text("EnemyPos %f.%f\n", charaBase_.pos_.x, charaBase_.pos_.y);
	ImGui::Text("moveEnemy%f.%f\n",  moveEnemy_.x, moveEnemy_.y);

	ImGui::End();

#pragma endregion
#endif // DEBUG


}

void NHEnemy::Draw()
{
#ifdef _DEBUG
	Novice::DrawEllipse(int(charaBase_.pos_.x), int(charaBase_.pos_.y), int(charaBase_.radius_), int(charaBase_.radius_), 0.0f, charaBase_.color_, kFillModeSolid);
#endif
	//アニメーションDraw
	animation_->Draw(charaBase_.color_);
}


