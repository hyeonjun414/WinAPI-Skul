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
            m_bIsFloor = false;

        }
    }
    break;
    }
}

void CStateIdle::OnCollisionEnter(CObject* _pObj, CCollider* _pOther)
{
    //switch (_pObj->GetObjGroup())
    //{
    //case OBJ_TYPE::PLAYER:
    //{
    //    CPlayer* pPlayer = (CPlayer*)_pObj;
    //    if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
    //    {
    //            m_bIsFloor = false;

    //    }
    //}
    //break;
    //}
}


void CStateIdle::OnCollisionExit(CObject* _pObj, CCollider* _pOther)
{
    //switch (_pObj->GetObjGroup())
    //{
    //case OBJ_TYPE::PLAYER:
    //{
    //    CPlayer* pPlayer = (CPlayer*)_pObj;
    //    if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
    //    {
    //            m_bIsFloor = false;

    //    }
    //}
    //break;
    //}
}