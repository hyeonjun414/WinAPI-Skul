#include "pch.h"
#include "CStateDash.h"
#include "CStateIdle.h"
#include "CStateMove.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEffect.h"

CState* CStateDash::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (KEYTAP(KEY::Z) && pPlayer->m_bCanSecondDash)
        {
            pPlayer->m_bCanSecondDash = false;
            return new CStateDash();
        }

        if (m_iCurMoveDist >= m_iDist)
            return new CStateIdle();

        return nullptr;
    }
    break;
    }
    return nullptr;
}
void CStateDash::Update(CObject* _pObj) {
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        // 플레이어가 바라보고 있는 방향으로 일정 거리만큼 빠른 속도로 이동
        if (pPlayer->m_bIsRight)
        {
            pPlayer->m_vPos.x += m_fDashSpeed * DT;
        }
        else
        {
            pPlayer->m_vPos.x -= m_fDashSpeed * DT;
        }
        m_iCurMoveDist += m_fDashSpeed * DT;
      
    }
    break;
    }
}

void CStateDash::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_iDist = 200;
        m_iCurMoveDist = 0;
        m_fDashSpeed = 700;
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->m_vPos.y -= 1;
        pPlayer->m_vVelocity.y = 0;
        pPlayer->GetAnimator()->Play(L"Player_Dash", true);
        CEffect* eft = new CEffect(OBJ_TYPE::EFFECT, L"Dash_Smoke", L"texture\\effect\\dash_smoke_midium.png",
            1, 1, 96, pPlayer->GetObjDir());
        CREATEOBJECT(eft);
        eft->SetPos(pPlayer->GetPos()+Vec2(0,-20));
        SINGLE(CSoundManager)->Play(L"Dash");
    }
    break;
    }
}

void CStateDash::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->m_bCanDash = false;
        pPlayer->m_fDashCurTime = 0;
    }
    break;
    }

}