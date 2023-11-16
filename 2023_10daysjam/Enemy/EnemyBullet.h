#pragma once
#include "Vector2.h"

//敵の攻撃クラス
class EnemyBullet 
{
public:

	bool enemy_isShot;
	Vector2 bulletPos;
	int bulletRadius;
	float bulletSpeed;

	EnemyBullet();
	~EnemyBullet();

	void Update();
	void Draw();

};

