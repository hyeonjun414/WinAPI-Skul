#include "pch.h"

#include "CStateMove.h"
#include "CStateIdle.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateMove::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (KEYAWAY(KEY::LEFT))
        {
            return new CStateIdle();
        }
        if (KEYAWAY(KEY::RIGHT))
        {
            return new CStateIdle();
        }
        if (KEYTAP(KEY::SPACE))
        {
            return new CStateJump();
        }
        if (!pPlayer->IsGround())
            return new CStateFall();
        return nullptr;
    }
    break;
    }
}
void CStateMove::Update(CObject* _pObj) {

    switch (_pObj->GetObjGroup())
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
    }
        break;
    }
}

void CStateMove::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        m_bIsFloor = true;
        pPlayer->GetAnimator()->Play(L"Player_Move", true);
    }
    break;
    }
}

void CStateMove::Exit(CObject* _pObj)
{
}

void CStateMove::OnCollision(CObject* _pObj, CCollider* _pOther)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
        {
            CCollider* pCol = pPlayer->GetCollider();
            Vec2 pos1 = pCol->GetFinalPos();
            Vec2 pos2 = _pOther->GetFinalPos();
            Vec2 size1 = pCol->GetScale();
            Vec2 size2 = _pOther->GetScale();
            if (pos2.y - size2.y / 2 <= pos1.y && pos1.y <= pos2.y + size2.y / 2)
            {
                if (pos1.x <= pos2.x - size2.x / 2)
                {
                    pPlayer->m_vPos.x = pos2.x + (-size1.x - size2.x) / 2 -5;
                }
                else if (pos1.x >= pos2.x + size2.x / 2)
                {
                    pPlayer->m_vPos.x = pos2.x + (size1.x + size2.x) / 2 +5;

                }
            }
        }
    }
    break;
    }
}

void CStateMove::OnCollisionEnter(CObject* _pObj, CCollider* _pOther)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
        {
            pPlayer->m_iCollCount++;
            if (pPlayer->m_iCollCount > 0)
                pPlayer->m_bIsGround = true;

        }
    }
    break;
    }
}


void CStateMove::OnCollisionExit(CObject* _pObj, CCollider* _pOther)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
        {
            pPlayer->m_iCollCount--;
            if (pPlayer->m_iCollCount <= 0)
            {
                pPlayer->m_iCollCount = 0;
                pPlayer->m_bIsGround = false;
            }
        }
    }
    break;
    }
}


