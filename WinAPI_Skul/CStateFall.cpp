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
        if (KEYTAP(KEY::SPACE))
        {

        }
        if (m_bIsFloor)
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
            pPlayer->SetPos(pPlayer->GetPos() + Vec2(-300 * DT, 0));
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->SetObjDir(true);
            pPlayer->SetPos(pPlayer->GetPos() + Vec2(300 * DT, 0));
        }

        m_vVelocity.y -= 700 * DT;
        pPlayer->SetPos(pPlayer->GetPos() + Vec2(0, -m_vVelocity.y * DT));

        if (m_vVelocity.y < -1)
        {
            pPlayer->GetAnimator()->Play(L"Player_Fall", true);
        }
        if (m_vVelocity.y < -200)
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
        m_vVelocity.y = 0;
        m_bIsFloor = false;
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->GetAnimator()->Play(L"Player_Fall", true);
    }
    break;
    }
}

void CStateFall::Exit(CObject* _pObj)
{
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
                m_bIsFloor = true;
        }
    }
    break;
    }
}
