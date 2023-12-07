#pragma once
#include "Object/Object.h"
class Apostel_MagicBall :public Object
{
public:
	~Apostel_MagicBall();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(CharaBase owner);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw()override;

	bool IsDead() { return isDead_; }

	bool GetDirection() {
		if (moveDirection_ < 0)
			return false;
		return true;
	}
	float GetAttackPoint() override { return attackPoint_; }
	EnemyType GetAttributeType() { return (EnemyType)attribute_; };
private:
	
	bool isDead_ = false;
	MaindState attribute_ = Normal;
	float jumpForce_ = 0;
	float fallSpeed_ = 0;
	int moveDirection_ = 1;
	float attackPoint_ = 30.f;
};

