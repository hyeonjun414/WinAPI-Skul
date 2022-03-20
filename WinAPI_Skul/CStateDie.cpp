#include "pch.h"
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

CState* CStateDie::HandleInput(CObject* _pObj)
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
        if (m_fCurTime >= m_fDuration)
        {
            DELETEOBJECT(_pObj);
            SINGLE(CGameManager)->m_iRemainEnemyCount--;
        }
    }
    break;
    }
    return nullptr;
}

void CStateDie::Update(CObject* _pObj)
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
        m_fCurTime += DT;

    }
    break;
    }
}

void CStateDie::Enter(CObject* _pObj)
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
        m_fCurTime = 0.f;
        m_fDuration = 2.5f;
        //pEnemy->GetAnimator()->Play(L"BigKnight_Die", true);
        pEnemy->GetAnimator()->PlayAndNextAnim(L"BigKnight_Die", false, L"DisappearEnemy");
    }
    break;
    }
}

void CStateDie::Exit(CObject* _pObj)
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
