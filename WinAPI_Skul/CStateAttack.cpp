#include "pch.h"
#include "CStateAttack.h"
#include "CStateIdle.h"
#include "CStateMove.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateAttack::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        
        // 공격 시간이 종료되었거나, 마지막 모션이 끝났을때
        if (m_fAttackLimitTime <= 0 || m_iAttackCount == 2)
            return new CStateIdle();

        if (KEYTAP(KEY::X))
            m_bAttackInput = true;

        
        return nullptr;
    }
    break;
    }
}
void CStateAttack::Update(CObject* _pObj) {
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        m_fFlowTime += DT;
        m_fAttackLimitTime -= DT;
        if (m_fFlowTime >= m_fAttackDelay && m_bAttackInput)
        {
            m_fFlowTime = 0;
            m_iAttackCount++;
            m_bAttackInput = false;
            m_fAttackLimitTime += m_fAttackDelay;
        }

        if (1 == m_iAttackCount && !m_bIsSecondAttack)
        {
            m_bIsSecondAttack = true;
            pPlayer->GetAnimator()->Play(L"Player_AttackB", true);
            SINGLE(CSoundManager)->Play(L"AttackB");
            if (KEYHOLD(KEY::LEFT))
            {
                pPlayer->m_bIsRight = false;
                pPlayer->m_vPos.x -= 30;
            }
            if (KEYHOLD(KEY::RIGHT))
            {
                pPlayer->m_bIsRight = true;
                pPlayer->m_vPos.x += 30;
            }
        }

    }
    break;
    }
}

void CStateAttack::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        m_fAttackDelay = 0.5f;
        m_fAttackLimitTime = m_fAttackDelay;
        m_iAttackCount = 0;
        m_fFlowTime = 0;
        m_bIsSecondAttack = false;
        m_bAttackInput = false;
        pPlayer->GetAnimator()->Play(L"Player_AttackA", true);
        SINGLE(CSoundManager)->Play(L"AttackA");

        if (KEYHOLD(KEY::LEFT))
        {
            pPlayer->m_bIsRight = false;
            pPlayer->m_vPos.x -= 30;
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->m_bIsRight = true;
            pPlayer->m_vPos.x += 30;
        }
    }
    break;
    }
}

void CStateAttack::Exit(CObject* _pObj)
{
}