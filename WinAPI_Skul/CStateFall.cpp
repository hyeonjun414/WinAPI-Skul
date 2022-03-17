#include "pch.h"

#include "CStateMove.h"
#include "CStateIdle.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateFall::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (pPlayer->IsGround())
            return new CStateIdle();
        return nullptr;
    }
    break;
    }
}

void CStateFall::Update(CObject* _pObj)
{
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
        pPlayer->m_vVelocity.y -= 700 * DT;
        pPlayer->m_vPos.y -= pPlayer->m_vVelocity.y * DT;

        if (pPlayer->m_vVelocity.y < -1)
        {
            pPlayer->GetAnimator()->Play(L"Player_Fall", true);
        }
        if (pPlayer->m_vVelocity.y < -200)
        {
            pPlayer->GetAnimator()->Play(L"Player_FallRepeat", true);
        }
    }
    break;
    }

}

void CStateFall::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_bIsFloor = false;
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->GetAnimator()->Play(L"Player_Fall", true);
    }
    break;
    }
}

void CStateFall::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->m_vVelocity.y = 0;
    }
    break;
    }
}

void CStateFall::OnCollision(CObject* _pObj, CCollider* _pOther)
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
                    pPlayer->m_vPos.x = pos2.x + (-size1.x - size2.x) / 2 -1;
                }
                else if (pos1.x >= pos2.x + size2.x / 2)
                {
                    pPlayer->m_vPos.x = pos2.x + (size1.x + size2.x) / 2 +1;

                }
            }
        }
    }
    break;
    }
}

void CStateFall::OnCollisionEnter(CObject* _pObj, CCollider* _pOther)
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


void CStateFall::OnCollisionExit(CObject* _pObj, CCollider* _pOther)
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