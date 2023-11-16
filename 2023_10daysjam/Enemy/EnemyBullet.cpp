#include "EnemyBullet.h"
#include "Novice.h"

EnemyBullet::EnemyBullet() 
{
	//初期化
	enemy_isShot = false;
	bulletPos.x = -100.f;
	bulletPos.y = -100.f;
	bulletRadius = 10;
	bulletSpeed = 4.0f;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update()
{
}

void EnemyBullet::Draw()
{
	Novice::DrawEllipse((int)bulletPos.x, (int)bulletPos.y, bulletRadius, bulletRadius, 0.f, WHITE, kFillModeSolid);
}

