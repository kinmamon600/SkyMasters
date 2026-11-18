#include "FighterData.h"

// ステータスの合算
FighterStatus CalculateFighterStatus(
    const BodyData& body,
    const WingData& wing,
    const DiffuserData& diffuser,
    const SpecialWeaponData& weapon)
{
    FighterStatus status;

    // 体力
    status.hp = body.hp + wing.hp + diffuser.hp;

    // 回転速度
    status.rotateSpeed =
        body.rotateSpeed + wing.rotateSpeed + diffuser.rotateSpeed;

    // 加速度
    status.accele =
        body.accele + wing.accele + diffuser.accele;

    // 通常攻撃力
    status.attackPower = body.attackPower;

    // スペシャル攻撃力
    status.specialAttack = weapon.specialAttack;

    return status;
}