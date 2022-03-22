#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateFall::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (pPlayer->IsGround())
            return new CStateIdle();

        if (KEYTAP(KEY::A) && pPlayer->m_bCanSkill)
        {
            return new CStateSkill();
        }
        if (KEYTAP(KEY::S) && !pPlayer->m_bCanSkill)
        {
            return new CStateAppear();
        }
        if (KEYTAP(KEY::X) && pPlayer->m_bCanJumpAttack)
        {
            return new CStateJumpAttack();
        }

        if (KEYTAP(KEY::C) && pPlayer->m_bCanDoubleJump)
        {
            pPlayer->m_bCanDoubleJump = false;
            return new CStateJump();
        }
        return nullptr;
        break;
    }
    case OBJ_TYPE::ENEMY:
    {
        CEnemy* pEnemy = (CEnemy*)_pObj;
        if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
            return new CStateDie();

        if (pEnemy->m_bIsGround)
            return new CStateIdle();
        break;
        switch (pEnemy->GetEnemyType())
        {
        case ENEMY_TYPE::BIG_KNIGHT:
        {
            CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        }
        break;
        }
        
    }
    }
    return nullptr;
}

void CStateFall::Update(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (KEYHOLD(KEY::LEFT))
        {
            pPlayer->SetObjDir(false);
            pPlayer->m_vPos.x -= pPlayer->m_vVelocity.x * DT;
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->SetObjDir(true);
            pPlayer->m_vPos.x += pPlayer->m_vVelocity.x * DT;
        }
        pPlayer->m_vVelocity.y += 1400 * DT;
        pPlayer->m_vPos.y += pPlayer->m_vVelocity.y * DT;

        if (pPlayer->m_vVelocity.y > 200)
        {
            if (pPlayer->m_bCanSkill)
                pPlayer->GetAnimator()->Play(L"Player_FallRepeat", true);
            else
                pPlayer->GetAnimator()->Play(L"Player_FallRepeat_Headless", true);
        }
        break;
    }
    case OBJ_TYPE::ENEMY:
    {
        CEnemy* pEnemy = (CEnemy*)_pObj;
        pEnemy->m_tEnemyInfo.m_vVelocity.y += 1400 * DT;
        pEnemy->m_vPos.y += pEnemy->m_tEnemyInfo.m_vVelocity.y * DT;
        switch (pEnemy->GetEnemyType())
        {
        case ENEMY_TYPE::BIG_KNIGHT:
        {
            CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        }
        break;
        }
        break;
    }
    }

}

void CStateFall::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (pPlayer->m_bCanSkill)
            pPlayer->GetAnimator()->Play(L"Player_Fall", true);
        else
            pPlayer->GetAnimator()->Play(L"Player_Fall_Headless", true);
        pPlayer->m_strCurState = L"Fall";
        break;
    }
    case OBJ_TYPE::ENEMY:
    {
        CEnemy* pEnemy = (CEnemy*)_pObj;
        switch (pEnemy->GetEnemyType())
        {
        case ENEMY_TYPE::BIG_KNIGHT:
        {
            CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
            pEnemy->GetAnimator()->Play(L"BigKnight_Idle", true);
            pEnemy->m_strCurState = L"Fall";
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            pEnemy->GetAnimator()->Play(L"Wizard_Idle", true);
            pEnemy->m_strCurState = L"Fall";
        }
        break;
        }
        break;
    }
    }
}

void CStateFall::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
    }
    break;
    }
}
