#pragma once
#include <list>
#include "CharaBase.h"
#include "Animation.h"
#include "Animation/PlayerIdolAnim.h"
#include "Animation/PlayerRunAnim.h"
#include "Function/UtilityStruct.h"
#include "Animation/PlayerAttackAnim1.h"
#include "Animation/PlayerAttack2Anim.h"
#include "Animation/Effect/LunaMental.h"
#include "Animation/PlayerJump.h"
#include "Animation/PlayerFall.h"

class PlayerAnimation
{
public:
    ~PlayerAnimation();
    PlayerAnimation();
    void Initialize();
    void Update(Vector2 pos, STATE main, SABSTATE sab);
    void SetDirection(bool right);
    void SetMaindState(const MaindState& state);
    void SetJumpSpeed(float num); //プレイヤーの上昇/下降判定用
    void Draw();
private:
    void AddLunaEffect(const Vector2& pos);
    int _lunaEffectTimer = 0;
    bool _isDirectionRight;
    PlayerIdolAnim* _idol = nullptr;
    PlayerRunAnim* _run = nullptr;
    PlayerAttackAnim1* _attack1 = nullptr;
    PlayerAttack2Anim* _attack2 = nullptr;
    PlayerJump* _jump = nullptr;
    PlayerFall* _fall = nullptr;
    Animation* _now = nullptr; //現在使うアニメーション
    Vector2 _pos;
    MaindState _maindState;
    std::list<LunaMentalEffect*> _lunaticEffect;
    float _jumpSpeed;

    UnitColor _defaultColor = defaultColor;
};

