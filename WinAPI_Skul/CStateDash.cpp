#include "pch.h"
#include "CStateDash.h"
#include "CStateIdle.h"
#include "CStateMove.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

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
}
void CStateDash::Update(CObject* _pObj) {
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        // �÷��̾ �ٶ󺸰� �ִ� �������� ���� �Ÿ���ŭ ���� �ӵ��� �̵�
        pPlayer->m_vPos.x += pPlayer->m_bIsRight ? 1 : -1 * m_fDashSpeed * DT;
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
        m_iDist = 150;
        m_iCurMoveDist = 0;
        m_fDashSpeed = 700;
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->GetAnimator()->Play(L"Player_Dash", true);
    }
    break;
    }
}

void CStateDash::Exit(CObject* _pObj)
{
}