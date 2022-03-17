#include "pch.h"

#include "CStateIdle.h"
#include "CStateMove.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"


CState* CStateIdle::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (KEYHOLD(KEY::LEFT))
        {
            pPlayer->SetObjDir(false);
            return new CStateMove();
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->SetObjDir(true);
            return new CStateMove();
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
void CStateIdle::Update(CObject* _pPlayer) {
}

void CStateIdle::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_bIsFloor = true;
        CPlayer* _pPlayer = (CPlayer*)_pObj;
        _pPlayer->GetAnimator()->Play(L"Player_Idle", true);
    }
    break;
    }
}

void CStateIdle::Exit(CObject* _pObj)
{
}

void CStateIdle::OnCollision(CObject* _pObj, CCollider* _pOther)
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
                    pPlayer->m_vPos.x = pos2.x + (-size1.x - size2.x) / 2;
                }
                else if (pos1.x >= pos2.x + size2.x / 2)
                {
                    pPlayer->m_vPos.x = pos2.x + (size1.x + size2.x) / 2;

                }
            }
        }
    }
    break;
    }
}

void CStateIdle::OnCollisionEnter(CObject* _pObj, CCollider* _pOther)
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


void CStateIdle::OnCollisionExit(CObject* _pObj, CCollider* _pOther)
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


