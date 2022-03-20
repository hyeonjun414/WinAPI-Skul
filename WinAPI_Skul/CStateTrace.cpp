#include "pch.h"
#include "CStateTrace.h"
#include "CStateDie.h"
#include "CStateMove.h"
#include "CStateIdle.h"
#include "CStateJump.h"
#include "CStateFall.h"
#include "CStateJumpAttack.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CEnemyMelee.h"

CState* CStateTrace::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
    }
    break;
    case OBJ_TYPE::ENEMY_MELEE:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (abs(PLAYERPOS.x - pEnemy->GetPos().x) > 400)
            return new CStateIdle();

        if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
            return new CStateDie();
        if (!pEnemy->m_bIsGround)
            return new CStateFall();
    }
    break;
    }
    return nullptr;
}

void CStateTrace::Update(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
    }
    break;
    case OBJ_TYPE::ENEMY_MELEE:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (PLAYERPOS.x > pEnemy->GetPos().x +1)
        {
            pEnemy->SetObjDir(true);
            pEnemy->m_vPos.x += pEnemy->m_tEnemyInfo.m_vVelocity.x * DT;
        }
        else if(PLAYERPOS.x < pEnemy->GetPos().x -1)
        {
            pEnemy->SetObjDir(false);
            pEnemy->m_vPos.x -= pEnemy->m_tEnemyInfo.m_vVelocity.x * DT;
        }
    }
    break;
    }
}

void CStateTrace::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
    }
    break;
    case OBJ_TYPE::ENEMY_MELEE:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        pEnemy->GetAnimator()->Play(L"BigKnight_Move", true);
    }
    break;
    }
}

void CStateTrace::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
    }
    break;
    case OBJ_TYPE::ENEMY_MELEE:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
    }
    break;
    }
}
