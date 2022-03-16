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
        if (!m_bIsFloor)
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
        CPlayer* _pPlayer = (CPlayer*)_pObj;

        if (KEYHOLD(KEY::LEFT))
        {

            _pPlayer->SetObjDir(false);
            _pPlayer->SetPos(_pPlayer->GetPos() + Vec2(-300 * DT, 0));
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            _pPlayer->SetObjDir(true);
            _pPlayer->SetPos(_pPlayer->GetPos() + Vec2(300 * DT, 0));
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
        CPlayer* _pPlayer = (CPlayer*)_pObj;
        m_bIsFloor = true;
        _pPlayer->GetAnimator()->Play(L"Player_Move", true);
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
        if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE &&
            pPlayer->GetCollider()->GetFinalPos().y < _pOther->GetFinalPos().y + 1 &&
            (pPlayer->GetCollider()->GetFinalPos().x < _pOther->GetFinalPos().x ||
             pPlayer->GetCollider()->GetFinalPos().x > _pOther->GetFinalPos().x  ))
        {
            m_bIsFloor = false;
        }
    }
    break;
    }
}

void CStateMove::OnCollisionEnter(CObject* _pObj, CCollider* _pOther)
{
    //switch (_pObj->GetObjGroup())
    //{
    //case OBJ_TYPE::PLAYER:
    //{
    //    CPlayer* pPlayer = (CPlayer*)_pObj;
    //    if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
    //    {
    //        m_bIsFloor = false;

    //    }
    //}
    //break;
    //}
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
            m_bIsFloor = false;
        }
    }
    break;
    }
}


